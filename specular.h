#pragma once
#include "material.h"

class Specular: public Material{
public:
    Specular(std::shared_ptr<Texture> texture, bool emitting);
    Ray scatter(const Ray& r, const Hit& h) const override;
};

