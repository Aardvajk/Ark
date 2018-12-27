#include "ModelBuffers.h"

#include "graphics/buffers/PreviewBuffer.h"
#include "graphics/buffers/FaceBuffer.h"
#include "graphics/buffers/PointBuffer.h"

#include "models/Model.h"

ModelBuffers::ModelBuffers(Model *model, Graphics *graphics, QObject *parent)
{
    preview = new PreviewBuffer(model, graphics, this);
    faces = new FaceBuffer(model, graphics, this);
    points = new PointBuffer(model, graphics, this);

    connect(model, SIGNAL(changed()), preview, SLOT(invalidate()));
    connect(model, SIGNAL(changed()), faces, SLOT(invalidate()));
    connect(model, SIGNAL(changed()), points, SLOT(invalidate()));
}
