#ifndef GRID_H
#define GRID_H

#include <GxMaths/GxVector.h>

float snapToGrid(float value, float grid);
Gx::Vec3 snapToGrid(const Gx::Vec3 &value, float grid);

float snapToGridCorner(float value, float grid);
Gx::Vec3 snapToGridCorner(const Gx::Vec3 &value, float grid);

#endif // GRID_H
