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
        //QFile f(iterator.next());
        //QString fileIndex = f.fileName();
        //QString lastBit = fileIndex.section("/", -1, -1);
        QImage img(iterator.next());
        qDebug() <<"file processing :" << img.format ();
        Filter fltr (img.constBits (),img.width () ,img.height ());

    }
}
