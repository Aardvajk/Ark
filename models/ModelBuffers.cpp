#include "ModelBuffers.h"

#include "graphics/buffers/PreviewBuffer.h"

#include "models/Model.h"

ModelBuffers::ModelBuffers(Model *model, Graphics *graphics, QObject *parent)
{
    preview = new PreviewBuffer(model, graphics, this);

    connect(model, SIGNAL(changed()), preview, SLOT(invalidate()));
}
