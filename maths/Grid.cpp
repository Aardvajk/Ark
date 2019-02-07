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

QDataStream &operator<<(QDataStream &ds, const Grid &g)
{
    return ds << g.valid() << g.value();
}

QDataStream &operator>>(QDataStream &ds, Grid &g)
{
    bool valid;
    float value;

    ds >> valid >> value;

    g = valid ? Grid(value) : Grid();

    return ds;
}

