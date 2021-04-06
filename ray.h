#pragma once
#include "vector3d.h"
#include "point3d.h"

class Ray{

public:
    Ray(Vector3D origin, Vector3D direction);
    Point3D at(double t) const;

    Vector3D origin;
    Vector3D direction;
};

std::ostream& operator <<(std::ostream& os, const Ray& ray);
