#include "diffuse.h"
#include "random.h"

Diffuse::Diffuse(std::shared_ptr<Texture> texture, bool emitting)
    :Material{"Diffuse", texture, emitting}{}

Ray Diffuse::scatter(const Ray &ray, const Hit &hit) const {
    Vector3D scattered = random_hemisphere(hit.normal);
    return Ray{hit.point, scattered};
}