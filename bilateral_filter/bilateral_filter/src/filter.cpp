#include <cmath>
#include "filter.h"
#include <iostream>

Filter::Filter(const std::uint8_t * in_image ,
    int width, int height, int ker, double bright):
    f_width(width + ker*2), f_height(height + ker*2),
    in_img( f_width * f_height),
    out_img(width * height) , k_shld(ker), brightPar (bright) {

        kernelSize = 2 * k_shld + 1;
        long j {0};
        std::cout << "f_width" << f_width << ";" << "f_height" << f_height  << std::endl;
        for (long i = 0; i < f_width *  f_height; ++i) {
            if (is_border (i)) {
                in_img [i] = 0;
            } else {
                in_img [i] = in_image[j++];
            }
        }
        fillBorder ();
        calcBrihtnessMask();
        calcDistanceMask ();
}

Filter::Coordinate Filter::indToCoordnt (long index) {
   Coordinate out (index % f_width, index / f_width);
   return out;
};

long Filter::coordntToInd (const Coordinate & coor) {
    long index =  (static_cast <long> (coor.y_hei)) * f_width + coor.x_wid;
    return index;
};

void Filter::run () {
    //iteration over all pixels
    long ind_out{0};
    for (long cell = 0; cell < f_width * f_height; ++cell) {
        // do not process the border
        if (is_border (cell)) {continue;}
        // sum weight * pixel
        double sum_pixel{0};
        // sum weight
        double sum_weight{0};

        //distance Mask stores enumerated coordinates
        for (auto && [coord, val] : distanceMask) {
            // pixel index by coordinate
            long pix_ind = reltCoorToIndex(coord, cell);
            int differenBriht = abs (in_img[pix_ind] - in_img [cell]);
            sum_weight +=  val * brightnessMask[differenBriht];
            sum_pixel += val * brightnessMask[differenBriht]*in_img[pix_ind];

            double weight =  val * brightnessMask[differenBriht];
            sum_weight +=  weight;
            sum_pixel += weight*in_img[pix_ind];
        }
        out_img [ind_out++] = static_cast <uint8_t> (sum_pixel/sum_weight);
        //out_img [ind_out++] = in_img[cell];
    }
}

bool  Filter::savePng(const QString & name) {
    QImage image(out_img.data(), f_width - k_shld*2, f_height - k_shld *2 ,f_width - k_shld *2, QImage::Format_Indexed8);
    return image.save(name + ".png");
}

//Saving the Brightness Difference Mask
void Filter::calcBrihtnessMask () {
    for (int i = 0; i < 256; ++i) {
        double val = - static_cast <double> (i*i/(2*(pow(brightPar,2))));
        brightnessMask [i] = exp (val);
    }
}
// Saving the distance Mask
void Filter::calcDistanceMask () {
    int stop = kernelSize / 2;
    int start = - stop;
    for (int x = start ; x <= stop ; ++x) {
        for (int y = start; y <= stop; ++y) {
            Coordinate cor (x,y);
            double val = exp (- static_cast <double> (x*x + y*y) / (2.0 * pow (kernelSize/2,2)));
            distanceMask.insert(std::pair<Coordinate, double> (cor, val) );
        }
    }
}

bool Filter::is_border (long cell) {
    // top_border
    if ( cell >= 0 && cell < (f_width - 1) * (kernelSize / 2) ) { return true; }
    // left_border
    if ( cell % f_width < (kernelSize / 2)) { return true; }
    // bottom
    if (  cell >= f_width * (f_height - (kernelSize  / 2))) { return true; }
    // right border
    if (cell % f_width >= f_width - (kernelSize / 2))  { return true; }
    return false;
}

//relative coordinates by point
long Filter::reltCoorToIndex (const Coordinate & coor, long startIndex) {
    return startIndex =startIndex
            + coor.y_hei * f_width + coor.x_wid;
}

//filling parts of the image, for filter interpolation
void Filter::fillBorder () {
    // fill along the top edge
    // left top point
    long leftTopPoint = coordntToInd (Coordinate (k_shld,k_shld));
    long leftBotPoint = coordntToInd (Coordinate (k_shld,f_height - k_shld - 1));
    long rightTopPoint = coordntToInd (Coordinate(f_width - k_shld - 1,k_shld));
    long rightBotPoint = coordntToInd (Coordinate(f_width-k_shld-1 ,f_height - k_shld-1));

    //top edge  filling
    for (long i_top = leftTopPoint ; i_top <= rightTopPoint ; ++i_top) {
        for (int j = k_shld; j > 0 ; --j) {
            in_img [i_top - j * f_width] = in_img [i_top + j * f_width];
        }
    }
    // fill along the  Left edge
    for (long i_left = leftTopPoint ; i_left <= leftBotPoint ; i_left += f_width ) {
        for (int j = k_shld; j >= 0 ; --j) {
            in_img.at(i_left-j) = in_img.at(i_left+j);
        }
    }
   // fill the bottom edge
    for (long i_bot = leftBotPoint; i_bot <= rightBotPoint; ++i_bot) {
        for (int j = k_shld; j > 0 ; --j) {
            in_img.at(i_bot + j * f_width) = in_img.at(i_bot - j * f_width);
        }
    }
    //fill the right edge
    for(long i_right = rightTopPoint; i_right <= rightBotPoint; i_right += f_width) {
        for (int j = k_shld; j > 0; --j) {
            in_img.at(i_right + j) = in_img.at (i_right - j);
        }
    }
    // fill left upper square
    for (long i  = 0; i < k_shld * f_width + k_shld ; i += f_width ) {
        for ( long j = i; j < i + k_shld ; ++j ) {
            int temp = (in_img.at(j+k_shld)+ in_img.at(j+k_shld*f_width))/2;
            in_img.at (j) = static_cast <uint8_t> (temp);
        }
    }
    //fill right upper square
    for (long i = f_width - k_shld  ; i <= f_width * k_shld; i += f_width ) {
        for (long j = i ; j <  i + k_shld ; ++j) {
            int temp = (in_img.at(j-k_shld) + in_img.at(j+k_shld*f_width))/2 ;
            in_img.at (j) = static_cast <uint8_t> (temp);
        }
    }
    //fill left botton square
    for (long i = (f_height - k_shld)*f_width; i < f_width * (f_height-1) + k_shld; i += f_width ) {
        for (long j = i; j < i + k_shld ; ++ j) {
            int temp = (in_img.at(j+k_shld) + in_img.at(j-k_shld*f_width))/2 ;
            in_img.at (j) = static_cast <uint8_t> (temp);
        }
    }
    //fill riht botton square
    for (long i = ((f_height - k_shld + 1)*f_width - k_shld ); i < f_width * f_height; i += f_width) {
        for (long j = i; j < i + k_shld ; ++ j) {
            int temp = (in_img.at(j-k_shld) + in_img.at(j-k_shld*f_width))/2;
            in_img.at (j) = static_cast <uint8_t> (temp);
        }
    }
}




