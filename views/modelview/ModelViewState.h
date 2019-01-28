#ifndef MODELVIEWSTATE_H
#define MODELVIEWSTATE_H

#include "maths/Projection.h"

#include <GxMaths/GxTransform.h>

class ModelViewState
{
public:
    ModelViewState() = default;

    Projection::Type projection;
    Gx::Transform camera;
};

#endif // MODELVIEWSTATE_H
