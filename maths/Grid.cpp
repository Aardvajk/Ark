#include "Grid.h"

float snapToGrid(float value, float grid)
{
    auto mod = std::fmod(value, grid);
    return (value - mod) + (mod >= (grid / 2) ? grid : 0);
}

Gx::Vec3 snapToGrid(const Gx::Vec3 &v, float grid)
{
    return Gx::Vec3(snapToGrid(v.x, grid), snapToGrid(v.y, grid), snapToGrid(v.z, grid));
}
