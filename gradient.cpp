#include "gradient.h"
#include "color.h"

Gradient::Gradient(std::string name, Color color)
    : Texture{name, color} {}

Color Gradient::uv(double u, double v) const {
    return Color{u, v, 0};
}