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
#include <thread>
#include <atomic>

#include <QString>
#include <QObject>
#include <QMessageBox>
#include <QDebug>

#include "component.h"
#include "mediator.h"

class UsbManager: public Component/*, public QObject*/
{
/*    Q_OBJECT

*/
  public:
    UsbManager();
    ~UsbManager();
    void startMonitorLoop();
    void stopMonitorLoop();

  private:
    enum ErrorCode		{NO_ERROR, UNKNOWN};
    enum State			{READY, BUSY};
    QString				m_mountPoint;
    QString				m_loglocation;
    udev*				m_udev;
    udev_monitor*		m_monitor;
    int					m_fd;
    std::thread			usbMonitoringLoop;
    std::atomic_bool	m_done{};

    void initCommandLine();
    void initUdev();
    void clearUdev();
    udev_device* getChildDevice(udev_device* parent, const char* subsystem);
    void enumerateCurrentUsbDevices();
    void enumerateUsbDevices();
    void monitorUsbDeviceLoop();
    void createErrorMsg(const QString&) const;
    bool isUsbDevice(udev_device*);
    QString getDeviceAction(udev_device*) const;
    bool isAction(udev_device*, const char*);
    bool isDeviceInitialized(udev_device*);

/*  private slots:
    void onDeviceAdd();
    void onDeviceRemove();
    void onDeviceMount();
    void onDeviceUnmount();
    void onDeviceRemount();
    void onSetMountLocation();
    void onLogging();
*/
  signals:
    void deviceAdd(udev_device*);
    void deviceRemove();
    void deviceMount();
    void deviceUnmount();
    void deviceRemount();

};


#endif //USBMANAGER_H
