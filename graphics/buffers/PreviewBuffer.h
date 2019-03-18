#ifndef PREVIEWBUFFER_H
#define PREVIEWBUFFER_H

#include "core/Render.h"

#include "graphics/RenderKey.h"

#include "graphics/buffers/Buffer.h"

#include <QtCore/QHash>

class Model;

class PreviewBuffer : public Buffer
{
    Q_OBJECT

public:
    PreviewBuffer(Model *model, Graphics *graphics, QObject *parent = nullptr);

    void render(Render::Type type, Graphics *graphics) const;

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const override;

private:
    Model *model;
    mutable QHash<RenderKey, QPair<unsigned, unsigned> > sections;
};

#endif // PREVIEWBUFFER_H
