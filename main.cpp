#include "traywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrayWindow w;
    UsbManager u;
    UsbNotifier n;
    Mediator(&w, &u, &n);
    return a.exec();
}
