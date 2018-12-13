#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QtCore/QObject>

#include <GxGraphics/GxGraphicsResource.h>

#include <QGxGraphics/QGxGraphicsDevice.h>

#include <pcx/resource_map.h>

class Graphics : public QObject
{
    Q_OBJECT

public:
    explicit Graphics(QObject *parent = nullptr);

    QGx::GraphicsDevice device;
    pcx::resource_map<Gx::GraphicsResource> resources;

signals:
    void render();
    void deviceReset();

private slots:
    void timeout();
};

#endif // GRAPHICS_H
