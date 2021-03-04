#ifndef FILTER_H
#define FILTER_H

#include <QImage>
#include <vector>
#include <array>
#include <QtCore>
#include <map>
#include <utility>

class Filter
{
private:
    QImage in_image;
    int f_width;
    int f_height;
    int kernelSize;
    int k_shld;
    double brightPar;
    std::vector <std::uint8_t>  in_img;
    std::vector <std::uint8_t> out_img;

    struct Coordinate
    {
        int x_wid;
        int y_hei;
        Coordinate(int x, int y) : x_wid{x}, y_hei{y} {
        }
    public:
        friend bool operator<(const Coordinate & left ,
                              const Coordinate & right) {
            return (left.x_wid < right.x_wid) || (left.x_wid == right.x_wid)
                    && (left.y_hei < right.y_hei);
        }
    };
private:
    std::map <Coordinate,double> distanceMask;
    std::array <double, 256> brightnessMask;
    Coordinate indToCoordnt (long index);
    long coordntToInd(const Coordinate & coor);
    long reltCoorToIndex(const Coordinate & coor, long startIndex);
    void calcDistanceMask ();
    void calcBrihtnessMask ();
    bool is_border (long index);
    void fillBorder ();
public:
    Filter() = delete;
    Filter(const std::uint8_t * in_image ,
        int width, int height, int kernel, double bright);
    bool savePng(const QString & name);
    void run();

};

#endif // FILTER_H
