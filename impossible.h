#pragma once
#include "material.h"

class Impossible : public Material{
public:
    Impossible(std::shared_ptr<Texture> texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};