#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "component.h"
#include <QtDebug>


class UsbNotifier: public Component
{
public:
    UsbNotifier();
    ~UsbNotifier();

private:
    void eventOccure();
};

#endif //NOTIFIER_H
