#pragma once
#include "texture.h"

class Gradient : public Texture{
public:
    Gradient(std::string name, Color color);
    Color uv(double u, double v) const override;
};