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
        Filter filter (img.constBits (),img.width () ,img.height (), 15, 20);
        filter.run ();
        QString outFileName = outputDir + name[0];
        filter.savePng (outFileName);
    }
}
