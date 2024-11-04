#include "swTriangle.h"

namespace sw {

bool Triangle::intersect(const Ray &ray, Intersection &isect) const {
    const auto e1 = vertices[1] - vertices[0];
    const auto e2 = vertices[2] - vertices[0];
    const auto n = e1 % e2;

    const auto P = ray.origin();
    const auto d = ray.direction();

    const auto m = -n * vertices[0];
    const auto t = (n * P + m) / (-n * d);

    if (t < ray.minT || t > ray.maxT) return false;

    const auto Q = P + t * d;

    const auto r = Q - vertices[0];

    const auto mag_n = n.magnitude();
    const auto e1xr = e1 % r;
    if (e1xr * n < 0) return false;
    const auto rxe2 = r % e2;
    if (rxe2 * n < 0) return false;
    const auto v = (e1xr).magnitude() / mag_n;
    const auto w = (rxe2).magnitude() / mag_n;

    if (v < 0 || w < 0 || v + w >= 1) return false;

    isect.hitT = t;
    isect.normal = n;
    isect.normal.normalize();
    isect.frontFacing = (-d * isect.normal) > 0.0f;
    if (!isect.frontFacing) isect.normal = -isect.normal;
    isect.position = Q;
    isect.material = material;
    isect.ray = ray;

    return true;
}

} // namespace sw
