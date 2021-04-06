#include "glass.h"
#include "ray.h"
#include "hit.h"
#include "random.h"

Glass::Glass(std::shared_ptr<Texture> texture, bool emitting)
    : Material{"Glass", texture, emitting}{}

Ray Glass::scatter(const Ray &ray, const Hit &hit) const {
    auto direction = ray.direction;
    auto normal = hit.normal;
    double n1 = 1.0;
    double n2 = 1.5;

    if(dot(direction, normal) > 0) { // ray and normal are same direction
        normal *= -1;
        std::swap(n1,n2); // n1 -> outside, n2 -> inside so swap
    }

    double cos_theta = -dot(direction, normal);
    double probability = schlick(cos_theta, n1/n2);

    if(random_double() < probability){
        auto reflected = reflect(direction, normal);
        return Ray{hit.point, reflected};
    }
    else{
        auto refracted = refract(direction, normal, n1/n2);
        return Ray{hit.point, refracted};
    }
}