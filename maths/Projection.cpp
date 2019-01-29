#include "Projection.h"

#include "graphics/RenderParams.h"

#include <GxMaths/GxRange.h>

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

float orthoUnit(float value)
{
    int sc = 300;

    int v = sc - (value > sc ? sc : value);
    float f = static_cast<float>(v) / static_cast<float>(sc);

    f = 1.0f - cos((M_PI / 2) * f);

    auto i = static_cast<int>(static_cast<float>(sc) * f);

    return i > 0 ? i : 1;
}

float orthoComponent(Projection::Type type, const Gx::Vec3 &pos)
{
    switch(type)
    {
        case Projection::Type::Top: return pos.y;
        case Projection::Type::Bottom: return -pos.y;
        case Projection::Type::Left: return -pos.x;
        case Projection::Type::Right: return pos.x;
        case Projection::Type::Front: return -pos.z;
        case Projection::Type::Back: return pos.z;

        default: return 0;
    }
}

}

void Projection::orthoDirections(Type type, Gx::Vec3 &up, Gx::Vec3 &right, Gx::Vec3 &forward)
{
    switch(type)
    {
        case Type::Top: up = { 0, 0, 1 }; right = { 1, 0, 0 }; forward = { 0, -1, 0 }; break;
        case Type::Bottom: up = { 0, 0, -1 }; right = { 1, 0, 0 }; forward = { 0, 1, 0 }; break;
        case Type::Left: up = { 0, 1, 0 }; right = { 0, 0, -1 }; forward = { 1, 0, 0 }; break;
        case Type::Right: up = { 0, 1, 0 }; right = { 0, 0, 1 }; forward = { -1, 0, 0 }; break;
        case Type::Front: up = { 0, 1, 0 }; right = { 1, 0, 0 }; forward = { 0, 0, 1 }; break;
        case Type::Back: up = { 0, 1, 0 }; right = { -1, 0, 0 }; forward = { 0, 0, -1 }; break;

        default: break;
    }
}

Gx::Matrix Projection::orthoMatrix(Type type, const Gx::SizeF &size, const Gx::Vec3 &pos)
{
    return Gx::Matrix::ortho(orthoSize(size, orthoUnit(orthoComponent(type, pos))), { -32767.0f, 32767.0f });
}

void Projection::clampOrthoZ(Type type, Gx::Vec3 &pos)
{
    switch(type)
    {
        case Type::Top: if(pos.y < 0) pos.y = 0; break;
        case Type::Bottom: if(pos.y > 0) pos.y = 0; break;
        case Type::Left: if(pos.x > 0) pos.x = 0; break;
        case Type::Right: if(pos.x < 0) pos.x = 0; break;
        case Type::Front: if(pos.z > 0) pos.z = 0; break;
        case Type::Back: if(pos.z < 0) pos.z = 0; break;

        default: break;
    }
}

Gx::Transform Projection::camera(Type type)
{
    switch(type)
    {
        case Type::Perspective: return Gx::Transform({ 0, 0, -6 }, { 0, 0 });

        case Type::Top: return Gx::Transform({ 0, 200, 0 }, { 0, M_PI / 2 });
        case Type::Bottom: return Gx::Transform({ 0, -200, 0 }, { 0, -M_PI / 2 });
        case Type::Left: return Gx::Transform({ -200, 0, 0 }, { M_PI / 2, 0 });
        case Type::Right: return Gx::Transform({ 200, 0, 0 }, { -M_PI / 2, 0 });
        case Type::Front: return Gx::Transform({ 0, 0, -200 }, { 0, 0 });
        case Type::Back: return Gx::Transform({ 0, 0, 200 }, { M_PI, 0 });

        default: return { };
    }
}

const char *Projection::toString(Type type)
{
    static const char *s[] = { "Perspective", "Top", "Bottom", "Left", "Right", "Front", "Back", "None" };

    return s[static_cast<int>(type)];
}
