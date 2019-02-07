#ifndef GRID_H
#define GRID_H

#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

class Grid
{
public:
    Grid() = default;
    explicit Grid(float value) : v(value) { }

    bool valid() const { return v; }
    float value() const { return *v; }

    QVariant variant() const { return v ? QVariant(*v) : QVariant(); }

    static float snap(float value, float grid);
    static Gx::Vec3 snap(const Gx::Vec3 &value, float grid);

    static float snapCorner(float value, float grid);
    static Gx::Vec3 snapCorner(const Gx::Vec3 &value, float grid);

private:
    pcx::optional<float> v;
};

Q_DECLARE_METATYPE(Grid)

QDataStream &operator<<(QDataStream &ds, const Grid &g);
QDataStream &operator>>(QDataStream &ds, Grid &g);

#endif // GRID_H
