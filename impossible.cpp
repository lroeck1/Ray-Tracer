#include "impossible.h"
#include "specular.h"

Impossible::Impossible(std::shared_ptr<Texture> texture, bool emitting)
        :Material{"Impossible", texture, emitting}{}

Ray Impossible::scatter(const Ray &ray, const Hit &hit) const {
    return Ray{hit.point, cross(ray.direction, hit.normal)};
}