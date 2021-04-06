#include "metal.h"
#include "random.h"

Metal::Metal(std::shared_ptr<Texture> texture, bool emitting, double fuzz)
    :Material{"Metal", texture, emitting}, fuzz{fuzz}{
}

Ray Metal::scatter(const Ray &ray, const Hit &hit) const {
    /*Vector3D specular = reflect(ray.direction, hit.normal);
    Vector3D diffuse = random_hemisphere(hit.normal);
    if(fuzz <= .5) {
        specular *= 1-fuzz;
        diffuse *= fuzz;
    }
    else{
        specular *= fuzz;
        diffuse *= fuzz;
    }
    return Ray{hit.point, specular+diffuse};*/

    Vector3D scattered = reflect(ray.direction, hit.normal) + fuzz*random_unit_vector();
    return Ray{hit.point, scattered};
}