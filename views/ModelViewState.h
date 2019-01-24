#ifndef MODELVIEWSTATE_H
#define MODELVIEWSTATE_H

#include "core/Projection.h"

#include <GxMaths/GxTransform.h>

class ModelViewState
{
public:
    ModelViewState() : projection(Projection::Type::Perspective) { }

    Projection::Type projection;

    Gx::Transform camera;
};

#endif // MODELVIEWSTATE_H
