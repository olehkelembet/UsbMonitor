#ifndef COMPONENT_H
#define COMPONENT_H

class IMediator;

class Component
{
protected:
    IMediator *mediator;
public:
    Component(IMediator *mediator = nullptr);
    void set_mediator(IMediator *mediator);

    enum Event {
        DEVICE_MOUNT,
        DEVICE_UNMOUNT,
        DEVICE_REMOUNT,
        DEVICE_ADD,
        DEVICE_REMOVE,
        APP_START,
        APP_QUIT
    };
};

#endif // COMPONENT_H

