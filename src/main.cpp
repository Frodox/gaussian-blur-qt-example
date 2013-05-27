#include "jpegfilter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JpegFilter w;
    w.show();
    
    return a.exec();
}
