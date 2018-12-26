#ifndef PREVIEWBUFFER_H
#define PREVIEWBUFFER_H

#include "graphics/buffers/Buffer.h"

class Model;

class PreviewBuffer : public Buffer
{
    Q_OBJECT

public:
    PreviewBuffer(Model *model, Graphics *graphics, QObject *parent = nullptr);

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const override;

private:
    Model *model;
};

#endif // PREVIEWBUFFER_H
