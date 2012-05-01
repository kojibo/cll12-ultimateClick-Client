#include <QtGui/QApplication>
#include "cll12_ultimateclick_client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cll12_ultimateClick_client w;
    w.show();
    
    return a.exec();
}
