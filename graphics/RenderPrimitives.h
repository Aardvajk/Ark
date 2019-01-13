#ifndef RENDERPRIMITIVES_H
#define RENDERPRIMITIVES_H

namespace Gx
{

class Vec2;
class Vec3;
class Color;

}

class Graphics;
class RenderParams;

namespace RenderPrimitives
{

void invertBox(Graphics *graphics, const RenderParams &params, const Gx::Vec2 &anc, const Gx::Vec2 &pos);

}

#endif // RENDERPRIMITIVES_H
