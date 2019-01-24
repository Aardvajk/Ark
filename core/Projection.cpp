#include "Projection.h"

#include "graphics/RenderParams.h"

#include <GxMaths/GxSize.h>
#include <GxMaths/GxVector.h>
#include <GxMaths/GxMatrix.h>
#include <GxMaths/GxRange.h>

#include <QtCore/QSize>

#include <cmath>

namespace
{

Gx::SizeF orthoSize(const Gx::SizeF &size, float pixelsPerUnit)
{
    if(size.width < size.height)
    {
        auto height = size.height / pixelsPerUnit;
        return { height * (size.width / size.height), height };
    }
    else
    {
        auto width = size.width / pixelsPerUnit;
        return { width, width * (size.height / size.width) };
    }
}

float orthoUnit(const Gx::Vec3 &pos, const Gx::SizeF &size, float fov)
{
    auto m = Gx::Matrix::lookAt(pos, pos + Gx::Vec3(0, 0, 1), Gx::Vec3(0, 1, 0)) * Gx::Matrix::perspective(fov, size.width / size.height, { 0.1f, 32767.0f });

    auto a = Gx::Vec3(-0.5, 0, 0).transformedCoord(m);
    auto b = Gx::Vec3(0.5f, 0, 0).transformedCoord(m);

    float ap = (size.width / 2.0f) * a.x;
    float bp = (size.width / 2.0f) * b.x;

    return std::fabs(ap - bp);
}

}

Gx::Matrix Projection::matrix(const RenderParams &params)
{
    switch(params.projection)
    {
        case Type::Perspective: return Gx::Matrix::perspective(params.fov, params.size.width / params.size.height, { 0.1f, 100.0f });
        case Type::Orthographic: return Gx::Matrix::ortho(orthoSize(params.size, orthoUnit(params.position, params.size, params.fov)), { -32767.0f, 32767.0f });

        default: return { };
    }
}

const char *Projection::toString(Type type)
{
    static const char *s[] = { "Perspective", "Orthographic", "None" };

    return s[static_cast<int>(type)];
}
