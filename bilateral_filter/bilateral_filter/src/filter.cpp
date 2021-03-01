#include "filter.h"
#include <iostream>



Filter::Filter(const std::uint8_t * in_image , int width, int height):
    f_width(width), f_height(height), in_img(width * height), out_img(width * height)
{


    for (int i = 0; i < f_width * f_height; ++i ) {
        if (i >= in_img.size()) {
            qDebug() <<"warning : file size > " << width << "x" << height;
            break;
        }
        if ( !(i % f_width)) { std::cout << std::endl;}
        in_img [i] = in_image[i];
        std::cout << static_cast <unsigned> (in_img [i]) << " " ;
        //if (i && !(i % f_width) ) { std::cout << std::endl;}
    }
}
