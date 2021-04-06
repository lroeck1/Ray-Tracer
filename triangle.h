#pragma once
#include "point3d.h"
#include "object.h"

class Triangle : public Object{
public:
    Triangle(Point3D vertex0, Point3D vertex1, Point3D vertex2, std::shared_ptr<Material>);

    bool intersect(const Ray& ray, double& time) const override;
    Hit construct_hit(double time, const Ray& ray) override;
    std::pair<double, double> uv(const Hit& hit) const override;

    Point3D vertex0, vertex1, vertex2;
    Vector3D edge1, edge2, normal;
    std::shared_ptr<Material> material;
};

std::ostream& operator <<(std::ostream& os, const Triangle& t);
