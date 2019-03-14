#ifndef RENDERPARAMS_H
#define RENDERPARAMS_H

#include "maths/Projection.h"

#include <GxMaths/GxSize.h>
#include <GxMaths/GxVector.h>
#include <GxMaths/GxMatrix.h>
#include <GxMaths/GxTransform.h>

class RenderParams
{
public:
    RenderParams(){ }

    Gx::SizeF size;
    float fov;
    Projection::Type projection;

    Gx::Matrix view;
    Gx::Matrix proj;

    Gx::Transform camera;
    Gx::Vec3 light;
};

#endif // RENDERPARAMS_H
