#pragma once
#include "material.h"

class Diffuse : public Material{
public:
    Diffuse(std::shared_ptr<Texture> texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};