#ifndef ORTHOGRID_H
#define ORTHOGRID_H

#include <GxMaths/GxColor.h>

class Graphics;
class RenderParams;

void renderOrthoGrid(Graphics *graphics, const RenderParams &params, float grid, const Gx::Color &color);

#endif // ORTHOGRID_H
