#pragma once
#include "texture.h"

class Checkerboard : public Texture{
public:
    Checkerboard(std::string name, Color color);
    Color uv(double u, double v) const override;
};