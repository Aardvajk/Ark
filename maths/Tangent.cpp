#include "Tangent.h"

#include <GxMaths/GxVector.h>

#include <cmath>

Gx::Vec3 calculateTangent(const Gx::Vec3 &v1, const Gx::Vec2 &t1, const Gx::Vec3 &v2, const Gx::Vec2 &t2, const Gx::Vec3 &v3, const Gx::Vec2 &t3, const Gx::Vec3 &normal)
{
    Gx::Vec3 tangent, bitangent;

    Gx::Vec3 edge1 = Gx::Vec3(v2 - v1).normalized();
    Gx::Vec3 edge2 = Gx::Vec3(v3 - v1).normalized();

    Gx::Vec2 texEdge1 = Gx::Vec2(t2 - t1).normalized();
    Gx::Vec2 texEdge2 = Gx::Vec2(t3 - t1).normalized();

    float det = (texEdge1.x * texEdge2.y) - (texEdge1.y * texEdge2.x);

    Gx::Vec3 bitangenttest;

    if(std::fabs(det) < 1e-6f)
    {
        tangent.x = 1.0f;
        tangent.y = 0.0f;
        tangent.z = 0.0f;

        bitangenttest.x = 0.0f;
        bitangenttest.y = 0.0f;
        bitangenttest.z = 1.0f;
    }
    else
    {
        det = 1.0f / det;

        tangent.x = (texEdge2.y * edge1.x - texEdge1.y * edge2.x) * det;
        tangent.y = (texEdge2.y * edge1.y - texEdge1.y * edge2.y) * det;
        tangent.z = (texEdge2.y * edge1.z - texEdge1.y * edge2.z) * det;

        bitangenttest.x = (-texEdge2.x * edge1.x + texEdge1.x * edge2.x) * det;
        bitangenttest.y = (-texEdge2.x * edge1.y + texEdge1.x * edge2.y) * det;
        bitangenttest.z = (-texEdge2.x * edge1.z + texEdge1.x * edge2.z) * det;

        tangent = tangent.normalized();
        bitangenttest = bitangenttest.normalized();
    }

    bitangent = normal.cross(tangent);

    float crossinv = ((bitangent.dot(bitangenttest)) < 0.0f) ? -1.0f : 1.0f;
    bitangent *= crossinv;

    return tangent;
}

