#pragma once
#include "material.h"

class Glass : public Material{
public:
    Glass(std::shared_ptr<Texture> texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;

};