#include "Graphics.h"

#include <QtCore/QTimer>

Graphics::Graphics(QObject *parent) : QObject(parent)
{
    auto timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(timeout()));

    timer->start(0);
}

void Graphics::timeout()
{
    bool reset = false;

    if(!device.isOk())
    {
        if(!device.isReadyToReset()) return;
        reset = true;
    }

    if(device.needsResetting())
    {
        reset = true;
    }

    if(reset)
    {
        for(auto &r: resources) if(r.isDeviceBound()) r.release();
        device.reset();
        for(auto &r: resources) if(r.isDeviceBound()) r.reset(device);

        emit deviceReset();
    }

    emit render();
}
