#pragma once
#include "point3d.h"
#include <memory>
#include "hit.h"
#include "object.h"

class Ray;
class Material;

class Sphere : public Object{
public:
    Sphere(Point3D center, double radius, std::shared_ptr<Material>);

    bool intersect(const Ray& ray, double& time) const override;
    Hit construct_hit(double time, const Ray& ray) override;
    std::pair<double, double> uv(const Hit& hit) const override;

    Point3D center;
    double radius;
    std::shared_ptr<Material> material;
};

std::ostream& operator <<(std::ostream& os, const Sphere& s);
