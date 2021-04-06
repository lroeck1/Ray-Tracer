#pragma once
#include <string>
#include "texture.h"
#include "ray.h"
#include "hit.h"
#include <memory>

class Material{
public:
    Material(std::string name, std::shared_ptr<Texture> texture, bool emitting);
    virtual Ray scatter(const Ray& r, const Hit& h) const = 0;

    std::string name;
    std::shared_ptr<Texture> texture;
    bool emitting;
};

std::ostream& operator <<(std::ostream& os, const Material& m);

Vector3D reflect(const Vector3D& vector, const Vector3D& normal);
Vector3D refract(const Vector3D& vector, const Vector3D& normal, double index_ratio);
double schlick(double cos_theta, double index_ratio);

