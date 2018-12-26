#ifndef POINTBUFFER_H
#define POINTBUFFER_H

#include "graphics/buffers/Buffer.h"

class Model;

class PointBuffer : public Buffer
{
    Q_OBJECT

public:
    PointBuffer(Model *model, Graphics *graphics, QObject *parent = nullptr);

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const override;

private:
    Model *model;
};

#endif // POINTBUFFER_H
