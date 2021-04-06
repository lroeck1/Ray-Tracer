#pragma once
#include "material.h"

class Metal : public Material{
public:
    Metal(std::shared_ptr<Texture> texture, bool emitting, double f);
    Ray scatter(const Ray& ray, const Hit& hit) const override;

    double fuzz;
};
