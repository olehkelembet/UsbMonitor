#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "component.h"

class TrayWindow;
class UsbManager;
class UsbNotifier;

class IMediator
{
public:
    virtual void notify(Component *sender, Component::Event event) const = 0;
};

class Mediator : public IMediator
{
private:
    TrayWindow* trayWnd;
    UsbManager* usbManager;
    UsbNotifier* usbNotifier;

public:
    Mediator(TrayWindow* c1, UsbManager* c2, UsbNotifier* c3);
    void notify(Component *sender,  Component::Event event) const override;
};

#endif // MEDIATOR_H

