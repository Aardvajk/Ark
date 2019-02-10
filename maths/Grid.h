#ifndef GRID_H
#define GRID_H

#include <GxMaths/GxVector.h>

namespace Grid
{

float snap(float value, float grid);
Gx::Vec3 snap(const Gx::Vec3 &value, float grid);

float snapCorner(float value, float grid);
Gx::Vec3 snapCorner(const Gx::Vec3 &value, float grid);

}

#endif // GRID_H
