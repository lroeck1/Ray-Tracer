#pragma once

#include "vector3d.h"
#include "point3d.h"
#include <memory>

class Material;

class Hit{
public:
    Hit(double time, Point3D point, Vector3D normal, std::shared_ptr<Material>);

    double time;
    Point3D point;
    Vector3D normal;
    std::shared_ptr<Material> material;
};

std::ostream& operator <<(std::ostream& os, const Hit& hit);
