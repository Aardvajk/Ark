#ifndef PREVIEWVERTEX_H
#define PREVIEWVERTEX_H

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxVertexDeclaration.h>

struct PreviewVertex
{
    Gx::Vec3 position;
    Gx::Vec3 normal;
    Gx::Rgba color;
    Gx::Vec2 texCoords;
    Gx::Vec3 tangent;

    static std::vector<Gx::VertexElement> declaration(){ return { Gx::VertexElement::Position, Gx::VertexElement::Normal, Gx::VertexElement::Color, Gx::VertexElement::TexCoord, Gx::VertexElement::Tangent }; }
};

#endif // PREVIEWVERTEX_H
