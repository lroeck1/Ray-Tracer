#include "material.h"

Material::Material(std::string name, std::shared_ptr<Texture> texture, bool emitting)
    :name{name}, texture{texture}, emitting{emitting}{}

std::ostream& operator <<(std::ostream& os, const Material& m){
    return os << m.name;
}

Vector3D reflect(const Vector3D& vector, const Vector3D& normal){
    return vector - 2*dot(vector, normal) * normal;
}

Vector3D refract(const Vector3D& vector, const Vector3D& normal, double index_ratio){
    double cos_theta = -dot(normal, vector);
    double discriminant = 1 - std::pow(index_ratio, 2) * (1-std::pow(cos_theta, 2));
    if (discriminant >= 0){
        return index_ratio * vector + (index_ratio * cos_theta - std::sqrt(discriminant)) * normal;
    }
    else { // total internal reflection
        return reflect(vector, normal);
    }
}

double schlick(double cos_theta, double index_ratio){
    double r0 = std::pow((1 - index_ratio) / (1 + index_ratio), 2);
    return r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
}