#include "usbmanager.h"



UsbManager::UsbManager()
                        : m_udev{nullptr}
                        , m_monitor{nullptr}
                        , m_fd{0}
{
  initUdev();
  monitorUsbDeviceLoop();
}

UsbManager::~UsbManager()
{
  clearUdev();
}

void UsbManager::onDeviceAdd()
{
    qDebug() << "Device added";
    emit deviceAdd();
}

void UsbManager::onDeviceRemove()
{

}

void UsbManager::onDeviceMount()
{

}

void UsbManager::onDeviceUnmount()
{

}
void UsbManager::onDeviceRemount()
{

}

void UsbManager::onSetMountLocation()
{

}

void UsbManager::onLogging()
{

}

void UsbManager::deviceAdd()
{

}

void UsbManager::deviceRemove()
{

}

void UsbManager::deviceMount()
{

}

void UsbManager::deviceUnmount()
{

}

void UsbManager::deviceRemount()
{

}

void UsbManager::initUdev()
{
  if(!m_udev)
  {
    m_udev = udev_new();
  }
}

void UsbManager::initCommandLine()
{

}

void UsbManager::enumerateCurrentUsbDevices()
{
  enumerateUsbDevices();
}

void UsbManager::clearUdev()
{
  if(m_udev)
    udev_unref(m_udev);
}

udev_device* UsbManager::getChildDevice(udev_device* parent, const char* subsystem)
{
  udev_device* child{nullptr};
  udev_enumerate* enumerate{nullptr};
  if(m_udev)
  {
      enumerate = udev_enumerate_new(m_udev);
  }
  else
  {
      createErrorMsg("Can't create udev!");
      return nullptr;
  }

  udev_enumerate_add_match_parent(enumerate, parent);
  udev_enumerate_add_match_subsystem(enumerate, subsystem);
  udev_enumerate_scan_devices(enumerate);

  udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
  udev_list_entry* entry;

  udev_list_entry_foreach(entry, devices) {
      const char *path = udev_list_entry_get_name(entry);
      child = udev_device_new_from_syspath(m_udev, path);
      break;
  }

  udev_enumerate_unref(enumerate);

  return child;
}

void UsbManager::enumerateUsbDevices()
{
    udev_enumerate* enumerate{nullptr};
    if(m_udev)
    {
        enumerate = udev_enumerate_new(m_udev);
    }
    else
    {
        createErrorMsg("Can't create udev!");
        return;
    }

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    udev_list_entry *devices{udev_enumerate_get_list_entry(enumerate)};
    udev_list_entry *entry{nullptr};

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        udev_device* scsi = udev_device_new_from_syspath(m_udev, path);

        udev_device* block = getChildDevice(scsi, "block");
        udev_device* scsi_disk = getChildDevice(scsi, "scsi_disk");

        //udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

        if (block)
            udev_device_unref(block);

        if (scsi_disk)
            udev_device_unref(scsi_disk);

        udev_device_unref(scsi);
    }

    udev_enumerate_unref(enumerate);
}

void UsbManager::monitorUsbDeviceLoop()
{
    m_monitor = udev_monitor_new_from_netlink(m_udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(m_monitor, "usb", NULL);
    udev_monitor_enable_receiving(m_monitor);
    m_fd = udev_monitor_get_fd(m_monitor);

    while (true)
    {
        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(m_fd, &fds);
        tv.tv_sec = 10;
        tv.tv_usec = 0;

        ret = select(m_fd+1, &fds, NULL, NULL, &tv);
        if(ret < 0)
            return;
        if(!FD_ISSET(m_fd, &fds))
            continue;

        udev_device* udevice = udev_monitor_receive_device(m_monitor);
        if(!udevice)
            continue;
        if(!isUsbDevice(udevice))
        {
            udev_device_unref(udevice);
            continue;
        }
        else
        {
            if(isAction(udevice, "bind") && isDeviceInitialized(udevice))
            {
                qInfo()<<"New device added.";
                emit deviceAdd();
            }
            else if(isAction(udevice, "unbind") && isDeviceInitialized(udevice))
            {
                qInfo()<<"Device removed.";
                emit deviceRemove();
            }
            else if(isAction(udevice, "add") && isDeviceInitialized(udevice))
                continue;
            else if(isAction(udevice, "remove") && isDeviceInitialized(udevice))
                continue;
            else
                qInfo()<<"Gone wrong.";

            udev_device_unref(udevice);
        }
        usleep(500*1000);
    }
}

void UsbManager::createErrorMsg(const QString& errorMessageStr) const
{
    QMessageBox::critical(nullptr, "Error ocured !", errorMessageStr);
}

bool UsbManager::isUsbDevice(udev_device* device)
{
    QString actual{udev_device_get_devtype(device)};
    QString needToBe("usb_device");

    return actual == needToBe;
}

QString UsbManager::getDeviceAction(udev_device* device) const
{
    return QString(udev_device_get_action(device));
}

bool UsbManager::isAction(udev_device* device, const char* action)
{
    return getDeviceAction(device) == action;
}

bool UsbManager::isDeviceInitialized(udev_device* device)
{
    return udev_device_get_is_initialized(device);
}
