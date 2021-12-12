#include "traywindow.h"
#include "usbmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrayWindow w;
    //UsbManager u;
//    w.show();
    return a.exec();
}
