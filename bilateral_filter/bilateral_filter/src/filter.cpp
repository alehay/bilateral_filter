#include <cmath>
#include "filter.h"
#include <iostream>



Filter::Filter(const std::uint8_t * in_image ,
               int width, int height, int kernel, double bright):
    f_width(width), f_height(height), in_img(width * height),
    out_img(width * height) , kernelSize(kernel), brightPar (bright)
{
    for (int i = 0; i < f_width * f_height; ++i ) {
        if (i >= in_img.size()) {
            qDebug() <<"warning : file size > " << width << "x" << height;
            break;
        }
        if ( !(i % f_width)) { std::cout << std::endl;}
        in_img [i] = in_image[i];

        #ifdef DEBUG
            std::cout << static_cast <unsigned> (in_img [i]) << " " ;
        #endif
    }
    calcBrihtnessMask();
    calcDistanceMask ();
}

Filter::Coordinate Filter::indToCoordnt (long index) {
   Coordinate out (index % f_width, index / f_width);
   return out;
};

long Filter::coordntToInd (Coordinate coor) {
    long index =  (static_cast <long> (coor.y_hei)) * f_width + coor.x_wid;
    return index;
};

void Filter::run () {
    for (int cell = 0; cell < f_width * f_height; ++cell) {
        if (is_border (cell)) {out_img[cell] = in_img[cell]; continue;}
        std::vector <std::uint8_t> neighbor (kernelSize*kernelSize);
        // test test test
        int start = cell - (kernelSize - 1) / 2 * f_width - (kernelSize - 1) / 2;
        int stop  = cell + (kernelSize - 1) / 2 * f_width + (kernelSize - 1) / 2;
        int index {0};
        double sum{0};

        for (auto && [coord, val]  : distanceMask) {
            sum += in_img [ coordntToInd (coord)];
        }
        out_img [cell] = sum/(kernelSize*kernelSize);
    }
}

//сохранение результата
bool  Filter::savePng(const QString & name) {
    QImage image(out_img.data(), f_width, f_height, QImage::Format_Indexed8);
    return image.save(name + ".png");
}

void Filter::calcBrihtnessMask () {
    for (int i = 0; i < 256; ++i) {
        double val = - static_cast <double> (i*i/(2*(pow(brightPar,2))));
        brightnessMask [i] = exp (val);
    #ifdef DEBUG
        std::cout << "BritnessMask " << i << " : " << brightnessMask[i] << std::endl;
    #endif
    }
}
void Filter::calcDistanceMask () {
    int stop = kernelSize / 2;
    int start = - stop;
    for (int x = start ; x <= stop ; ++x) {
        for (int y = start; y <= stop; ++y) {
            Coordinate cor (x,y);
            double val = exp (- static_cast <double> (x*x + y*y) / (pow (kernelSize,2)));
            distanceMask.insert(std::pair<Coordinate, double> (cor, val) );

        #ifdef DEBUG
            std::cout << "Distanse Mask " << "x : " << x
                      << " ; "             << "y : " << y << "\t"
                      << "value : " << val << std::endl;
        #endif
        }
    }
}

bool Filter::is_border (long index) {
    // верхняя
    if ( index >= 0 && index <= f_width * (kernelSize - 1) / 2) { return true; }
    // левая граница
    if ( index % f_width < (kernelSize - 1) / 2) { return true; }
    // нижняя
    if (  index >= f_width * (f_height - (kernelSize - 1) / 2)) { return true; }
    // правая
    if (index % f_width >= f_width - (kernelSize - 1) / 2)  { return true; }
    return false;
}





