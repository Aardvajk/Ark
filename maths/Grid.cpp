#include "Grid.h"

float Grid::snap(float value, float grid)
{
    auto mod = std::fmod(value, grid);
    return (value - mod) + (mod >= (grid / 2) ? grid : 0);
}

Gx::Vec3 Grid::snap(const Gx::Vec3 &value, float grid)
{
    return Gx::Vec3(snap(value.x, grid), snap(value.y, grid), snap(value.z, grid));
}

float Grid::snapCorner(float value, float grid)
{
    return value - std::fmod(value, grid);
}

Gx::Vec3 Grid::snapCorner(const Gx::Vec3 &value, float grid)
{
    return Gx::Vec3(snapCorner(value.x, grid), snapCorner(value.y, grid), snapCorner(value.z, grid));
}

