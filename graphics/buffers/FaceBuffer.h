#ifndef FACEBUFFER_H
#define FACEBUFFER_H

#include "graphics/buffers/Buffer.h"

class Model;

class FaceBuffer : public Buffer
{
    Q_OBJECT

public:
    enum class Type { Wireframe, Selection };

    FaceBuffer(Type type, Model *model, Graphics *graphics, QObject *parent = nullptr);

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const override;

private:
    Type type;
    Model *model;
};

#endif // FACEBUFFER_H
