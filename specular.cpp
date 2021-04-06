#include "specular.h"

Specular::Specular(std::shared_ptr<Texture> texture, bool emitting)
    :Material{"Specular", texture, emitting} {}

Ray Specular::scatter(const Ray &r, const Hit &h) const {
    Vector3D reflected = reflect(r.direction, h.normal);
    return Ray{h.point, reflected};
}