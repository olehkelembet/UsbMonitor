#include "mediator.h"
#include "traywindow.h"
#include "usbmanager.h"
#include "notifier.h"

Mediator::Mediator(TrayWindow *tray,
                   UsbManager* umanager,
                   UsbNotifier* unotifier):
                                           trayWnd(tray),
                                           usbManager(umanager),
                                           usbNotifier(unotifier)
{
    trayWnd->set_mediator(this);
    usbManager->set_mediator(this);
    usbNotifier->set_mediator(this);

    umanager->startMonitorLoop();

    /*QThread* thread = QThread::create([]{startMonitorLoop;});
    thread->start();*/
}

void Mediator::notify([[maybe_unused]]Component *sender, Component::Event e) const
{
    switch (e) {
      case Component::DEVICE_MOUNT:
        qInfo()<<"ulala!!!!!";
        break;
      case Component::DEVICE_UNMOUNT:
        break;
      case Component::DEVICE_REMOUNT:
        break;
      case Component::DEVICE_ADD:
        break;
      case Component::DEVICE_REMOVE:
        break;
      case Component::APP_START:
        qInfo()<<"i'm started !";
        break;
      case Component::APP_QUIT:
        usbManager->stopMonitorLoop();
        qInfo()<<"i'm stopped !";
        break;
    }
}

