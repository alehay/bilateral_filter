#define DEBUG

#include <QtCore>
//#include <QCoreApplication>
#include <QImage>
#include <iostream>
// #include <QDir>

#include "src/filter.h"

int main(int argc, char *argv[])
{
    QString inputDir = "in/";
    QString outputDir = "out/";

    QString path = QDir::currentPath() + "/" + inputDir;
    QDir dir(path);
    QDirIterator iterator(dir.absolutePath(), {"*.png"}, QDir::Files);

    while (iterator.hasNext()) {
        QImage img(iterator.next());
        QString fileIndex = iterator.fileName();
        QString lastBit = fileIndex.section("/", -1, -1);
        QStringList name = lastBit.split('.');
        for (int k = 5; k < 30; k += 5) {
            for (int d = 5; d <= 50 ; d += 10){
                Filter filter (img.constBits (),img.width () ,img.height (), k, d);
                filter.run ();
                QString num;
                num = "__k" + QString::number (k)+"__d" + QString::number(d);
                QString outFileName = outputDir + name[0] + num ;
                filter.savePng (outFileName);

            }
        }
        //Filter filter (img.constBits (),img.width () ,img.height (), 5, 5);
        //filter.run ();
        //QString outFileName = outputDir + name[0];
        //filter.savePng (outFileName);
    }
}
