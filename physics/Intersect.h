#ifndef INTERSECT_H
#define INTERSECT_H

#include "core/Element.h"
#include "core/Selection.h"

namespace Gx
{

class Matrix;
class Ray;

}

class Entity;
class QRectF;

Selection rayIntersect(Element::Type type, const Entity &entity, const Gx::Ray &ray, float &dist, bool visibleOnly);
Selection rectIntersect(Element::Type type, const Entity &entity, const QRectF &clip, const Gx::Matrix &transform, bool visibleOnly);

#endif // INTERSECT_H
