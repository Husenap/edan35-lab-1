#include "swIntersection.h"

namespace sw {

Ray Intersection::getShadowRay(const Vec3 &lightPos) {
    Vec3 L = lightPos - position;
    float tMax = sqrt(L * L);
    return Ray(position, L.normalize(), 0.01f, tMax);
}

Ray Intersection::getReflectedRay(void) {
    Vec3 N = normal;
    const Vec3 I = ray.dir;

    Vec3 R = I - 2 * (N * I) * N;

    return Ray(position, R, 0.01f, FLT_MAX);
}

Ray Intersection::getRefractedRay(void) {
    const Vec3 I = ray.dir;
    Vec3 N = normal;
    float eta = 1.0f / material.refractiveIndex;
    if (!frontFacing) eta = 1.0f / eta; // Inside material.

    const auto r = -I * N;
    const auto c = 1 - eta * eta * (1 - r * r);

    if (c < 0) {
        return getReflectedRay();
    }

    const auto R = eta * I + (eta * r - std::sqrt(c)) * N;

    return Ray(position, R, 0.01f, FLT_MAX);
}

} // namespace sw
