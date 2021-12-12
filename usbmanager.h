#ifndef USBMANAGER_H
#define USBMANAGER_H

#include <unistd.h>
#include <libudev.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <sys/utsname.h>
#include <libudev.h>
#include <getopt.h>

#include <QString>
#include <QObject>


class UsbManager
{
  public:
    UsbManager();
    ~UsbManager();

  private:
    enum ErrorCode	{NO_ERROR, UNKNOWN};
    enum State		{READY, BUSY};
    QString			loglocation;
    udev*			m_udev;

    void initCommandLine();
    void initUdev();
    void clearUdev();
    udev_device* getChildDevice(udev_device* parent, const char* subsystem);
    void enumerateCurrentUsbDevices();
    void enumerateUsbDevices();
    void monitorUsbDeviceLoop();

  private slots:
    void onDeviceAdd();
    void onDeviceRemove();
    void onDeviceMount();
    void onDeviceUnmount();
    void onDeviceRemount();
    void onSetMountLocation();
    void onLogging();

  signals:
    void deviceAdd();
    void deviceRemove();
    void deviceMount();
    void deviceUnmount();
    void deviceRemount();
};


#endif //USBMANAGER_H
