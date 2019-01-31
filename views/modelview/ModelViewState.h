#ifndef MODELVIEWSTATE_H
#define MODELVIEWSTATE_H

#include "core/Render.h"

#include "maths/Projection.h"

#include <GxMaths/GxTransform.h>

class ModelViewState
{
public:
    ModelViewState() = default;

    Projection::Type projection;
    Render::Type render;

    Gx::Transform camera;
};

#endif // MODELVIEWSTATE_H
