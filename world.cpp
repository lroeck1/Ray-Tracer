#include "world.h"
#include "object.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "triangle.h"


void World::add_sphere(Point3D center, double radius, std::shared_ptr<Material> material) {
    auto s = std::make_shared<Sphere>(center, radius, material); // instead of using New
    objects.push_back(s);
}

void World::add_triangle(Point3D vertex0, Point3D vertex1, Point3D vertex2, std::shared_ptr<Material> material) {
    auto s = std::make_shared<Triangle>(vertex0, vertex1, vertex2, material); // instead of using New
    objects.push_back(s);
}

Nearest World::find_nearest_object(const Ray &ray) const {
    double time = Constants::Infinity;
    std::shared_ptr<Object> nearest = nullptr;
    for (auto object : objects){
        double t;
        if(object->intersect(ray, t) && (t < time)){
            time = t;
            nearest = object;
        }
    }
    return {time,nearest};
}
