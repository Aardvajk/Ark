#ifndef INTERSECT_H
#define INTERSECT_H

#include "core/Element.h"

#include "properties/custom/Selection.h"

namespace Gx
{

class Matrix;

}

class Entity;
class QRectF;

Selection rectIntersect(Element::Type type, const Entity &entity, const QRectF &clip, const Gx::Matrix &transform, bool visibleOnly);

#endif // INTERSECT_H
