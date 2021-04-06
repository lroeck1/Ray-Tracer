#include "texture.h"

class Solid : public Texture{
public:
    Solid(std::string name, Color color);

    Color uv(double u, double v) const override;
};