/* TODO: Documentation, licanse
 */

#include <QApplication>
#include <QTextCodec>
#include "jpegfilter.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);
    JpegFilter w;
    w.show();

    return a.exec();
}
