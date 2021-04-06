#pragma once

#include "point3d.h"
#include <memory>
#include <vector>

class Object;
class Ray;
class Material;

using Nearest = std::pair<double, std::shared_ptr<Object>>;

class World{
public:
    void add_sphere(Point3D center, double radius, std::shared_ptr<Material>);
    void add_triangle(Point3D vertex0, Point3D vertex1, Point3D vertex2, std::shared_ptr<Material>);
    Nearest find_nearest_object(const Ray & ray) const;
    std::vector<std::shared_ptr<Object>> objects;
};