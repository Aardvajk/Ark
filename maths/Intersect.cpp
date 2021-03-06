#include "Intersect.h"

#include "core/Mesh.h"

#include "entity/Entity.h"

#include <GxMaths/GxMatrix.h>
#include <GxMaths/GxRay.h>

#include <QtGui/QPolygonF>

#include <numeric>

namespace
{

bool facing(const QPolygonF &p)
{
    if(p.count() < 3) return false;

    QPointF a = (p[1] - p[0]);
    QPointF b = (p[2] - p[1]);

    return Gx::Vec2(-a.y(), a.x()).dot(Gx::Vec2(b.x(), b.y())) < 0;
}

bool canSelectFace(const Entity &entity, int face, bool visibleOnly)
{
    return !visibleOnly || entity.subProperty(Element::Type::Face, face, "Visible").value<bool>();
}

}

Selection rayIntersect(Element::Type type, const Entity &entity, const Gx::Ray &ray, float &dist, bool visibleOnly)
{
    auto &mesh = entity.mesh();

    int closest = -1;
    float min = std::numeric_limits<float>::max();;

    if(type == Element::Type::Object || type == Element::Type::Face)
    {
        for(int i = 0; i < mesh.faces.count(); ++i)
        {
            for(int j = 1; j < mesh.faces[i].elements.count() - 1; ++j)
            {
                if(canSelectFace(entity, i, visibleOnly))
                {
                    auto a = mesh.vertex(i, 0);
                    auto b = mesh.vertex(i, j);
                    auto c = mesh.vertex(i, j + 1);

                    auto n = Gx::Vec3(b - a).cross(c - a).normalized();;

                    auto d = ray.intersectsTriFacing(a, b, c, n);
                    if(d && *d < min)
                    {
                        min = *d;
                        closest = i;
                    }
                }
            }
        }
    }
    else if(type == Element::Type::Vertex)
    {
        for(int i = 0; i < mesh.vertices.count(); ++i)
        {
            auto d = ray.intersectsSphere(mesh.vertices[i], 0.1f);
            if(d && *d < min)
            {
                min = *d;
                closest = i;
            }
        }
    }

    if(closest != -1)
    {
        dist = min;

        switch(type)
        {
            case Element::Type::Object: return Selection::fromElements(Element::Type::Face, mesh.faces.count());
            case Element::Type::Face: return Selection({ closest }, { });
            case Element::Type::Vertex: return Selection({ }, { closest });

            default: break;
        }
    }

    return Selection();
}

Selection rectIntersect(Element::Type type, const Entity &entity, const QRectF &clip, const Gx::Matrix &transform, bool visibleOnly)
{
    auto &mesh = entity.mesh();

    if(type == Element::Type::Object || type == Element::Type::Face)
    {
        QSet<int> faces;

        for(int i = 0; i < mesh.faces.count(); ++i)
        {
            if(canSelectFace(entity, i, visibleOnly))
            {
                bool ahead = false;

                QPolygonF pf;
                for(int j = 0; j < mesh.faces[i].elements.count(); ++j)
                {
                    auto v = mesh.vertex(i, j).transformedCoord(transform);
                    if(v.z <= 1.0f)
                    {
                        ahead = true;
                    }

                    pf.append(QPointF(v.x, v.y));
                }

                if(ahead && facing(pf) && !pf.intersected(clip).isEmpty())
                {
                    if(type == Element::Type::Object)
                    {
                        return Selection::fromElements(Element::Type::Face, mesh.faces.count());
                    }

                    faces.insert(i);
                }
            }
        }

        return Selection(faces, { });
    }
    else if(type == Element::Type::Vertex)
    {
        QSet<int> vertices;

        for(int i = 0; i < mesh.vertices.count(); ++i)
        {
            auto v = mesh.vertices[i].transformedCoord(transform);
            if(v.z < 1.0f && clip.contains(v.x, v.y))
            {
                vertices.insert(i);
            }
        }

        return Selection({ }, vertices);
    }

    return Selection();
}
