#include "Grid.h"

float snapToGrid(float value, float grid)
{
    auto mod = std::fmod(value, grid);
    return (value - mod) + (mod >= (grid / 2) ? grid : 0);
}

Gx::Vec3 snapToGrid(const Gx::Vec3 &value, float grid)
{
    return Gx::Vec3(snapToGrid(value.x, grid), snapToGrid(value.y, grid), snapToGrid(value.z, grid));
}

float snapToGridCorner(float value, float grid)
{
    return value - std::fmod(value, grid);
}

Gx::Vec3 snapToGridCorner(const Gx::Vec3 &value, float grid)
{
    return Gx::Vec3(snapToGridCorner(value.x, grid), snapToGridCorner(value.y, grid), snapToGridCorner(value.z, grid));
}

