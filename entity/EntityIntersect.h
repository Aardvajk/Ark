#ifndef ENTITYINTERSECT_H
#define ENTITYINTERSECT_H

#include "properties/custom/Selection.h"

class Entity;
class QRectF;

namespace Gx
{

class Ray;
class Matrix;

}

Selection rayIntersect(Selection::Type type, const Entity &entity, const Gx::Ray &ray, float &dist);
Selection rectIntersect(Selection::Type type, const Entity &entity, const QRectF &clip, const Gx::Matrix &transform);

#endif // ENTITYINTERSECT_H
