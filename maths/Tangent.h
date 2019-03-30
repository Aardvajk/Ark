#ifndef TANGENT_H
#define TANGENT_H

namespace Gx
{

class Vec2;
class Vec3;

}

Gx::Vec3 calculateTangent(const Gx::Vec3 &v1, const Gx::Vec2 &t1, const Gx::Vec3 &v2, const Gx::Vec2 &t2, const Gx::Vec3 &v3, const Gx::Vec2 &t3, const Gx::Vec3 &normal);

#endif // TANGENT_H
