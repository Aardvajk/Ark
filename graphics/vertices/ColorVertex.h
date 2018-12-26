#ifndef COLORVERTEX_H
#define COLORVERTEX_H

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxVertexDeclaration.h>

struct ColorVertex
{
    Gx::Vec3 position;
    Gx::Rgba color;

    static std::vector<Gx::VertexElement> declaration(){ return { Gx::VertexElement::Position, Gx::VertexElement::Color }; }
};

#endif // COLORVERTEX_H
