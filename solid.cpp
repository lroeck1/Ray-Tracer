#include "solid.h"

Solid::Solid(std::string name, Color color)
    : Texture{name, color}{}

Color Solid::uv(double, double) const {
    return color;
}