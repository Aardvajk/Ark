#ifndef FACEBUFFER_H
#define FACEBUFFER_H

#include "graphics/buffers/Buffer.h"

class Model;

class FaceBuffer : public Buffer
{
    Q_OBJECT

public:
    FaceBuffer(Model *model, Graphics *graphics, QObject *parent = nullptr);

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const override;

private:
    Model *model;
};

#endif // FACEBUFFER_H
