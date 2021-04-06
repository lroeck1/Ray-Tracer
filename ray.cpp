#include "ray.h"

Ray::Ray(Vector3D origin, Vector3D direction)
: origin{origin}, direction{unit(direction)} {}

 Point3D Ray::at(double t) const {
    return origin + direction * t;
}

std::ostream& operator <<(std::ostream& os, const Ray& ray){
    os << "Ray(origin=" << ray.origin << ", direction=" << ray.direction
       << ")";
    return os;
}