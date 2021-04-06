#include "checkerboard.h"

Checkerboard::Checkerboard(std::string name, Color color)
    : Texture{name, color} {}

Color Checkerboard::uv(double u, double v) const {
    int U = static_cast<int>(u*12) % 2;
    int V = static_cast<int>(v*6) % 2;
    if ((U+V) %2 == 0){
        return color;
    }
    else{
        return Black;
    }
}