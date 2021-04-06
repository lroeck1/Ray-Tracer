#pragma once
#include <string>
#include <memory>
#include "material.h"

class Object{
public:
    Object();
    Object(std::shared_ptr<Material> material);

    virtual bool intersect(const Ray& ray, double& time) const = 0;
    virtual Hit construct_hit(double time, const Ray& ray) = 0;
    virtual std::pair<double, double> uv(const Hit& hit) const = 0;

    std::shared_ptr<Material> material;
};