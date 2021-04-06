#pragma once
#include <string>
#include "color.h"

class Texture{
public:
    Texture(std::string name, Color color);

    virtual Color uv(double u, double v) const = 0;

    std::string name;
    Color color;
};