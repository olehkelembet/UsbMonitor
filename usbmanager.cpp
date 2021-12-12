#include "usbmanager.h"



UsbManager::UsbManager()
{
  initUdev();
}

UsbManager::~UsbManager()
{
  clearUdev();
}

void UsbManager::onDeviceAdd()
{

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
  udev_device* child = nullptr;
  udev_enumerate* enumerate = udev_enumerate_new(m_udev);

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
    udev_enumerate* enumerate = udev_enumerate_new(m_udev);

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        udev_device* scsi = udev_device_new_from_syspath(m_udev, path);

        udev_device* block = getChildDevice(scsi, "block");
        udev_device* scsi_disk = getChildDevice(scsi, "scsi_disk");

        udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

        if (block) {
            udev_device_unref(block);
        }

        if (scsi_disk) {
            udev_device_unref(scsi_disk);
        }

        udev_device_unref(scsi);
    }

    udev_enumerate_unref(enumerate);
}

void UsbManager::monitorUsbDeviceLoop()
{

}
