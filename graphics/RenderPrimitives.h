#ifndef RENDERPRIMITIVES_H
#define RENDERPRIMITIVES_H

#include "graphics/RenderState.h"

namespace Gx
{

class Vec2;
class Vec3;
class Color;

}

class Graphics;
class RenderParams;
class Mesh;

namespace RenderPrimitives
{

void screenBox(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec2 &anc, const Gx::Vec2 &pos, const Gx::Color &color);
void screenCircle(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec2 &pos, float radius, int slices, const Gx::Color &color);
void wireframeMesh(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Mesh &mesh, const Gx::Color &color);
void cursor(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec3 &pos, const Gx::Color &color);

}

#endif // RENDERPRIMITIVES_H
