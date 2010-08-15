/* QT 4.x ile Türkçe İngilizce Sözlük Uygulaması
Osman Yuksel  <yuxel (at) sonsuzdongu (dot) com>
13.09.2006
*/


#include <QApplication>
#include "sozluq.h"

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);
    Sozluq sozluk;
    sozluk.resize(300,530);
    sozluk.show();
    return app.exec();
}
