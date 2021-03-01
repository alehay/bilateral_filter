#ifndef FILTER_H
#define FILTER_H

#include <QImage>
#include <vector>
#include <QtCore>

class Filter
{
private:
    QImage in_image;
    int f_width;
    int f_height;
    std::vector <std::uint8_t>  in_img;
    std::vector <std::uint8_t> out_img;

public:
    Filter() = delete;
    Filter (const std::uint8_t * in_image , int width, int height);
};

#endif // FILTER_H
