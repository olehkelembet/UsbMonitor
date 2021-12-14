#include "traywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrayWindow w;
    return a.exec();
}
