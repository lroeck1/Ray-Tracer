// Lucas Roecker

#include "vector3d.h"
#include <iostream>
#include <stdexcept>

Vector3D::Vector3D():
        x{0.0}, y{0.0}, z{0.0} {}

Vector3D::Vector3D(double x, double y, double z): x{x}, y{y}, z{z} {}

Vector3D& Vector3D::operator+=(const Vector3D &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D& Vector3D::operator/=(const double scalar) {
    if(scalar == 0)
        throw std::overflow_error("Attempted to divide by Zero\n");
    x *= (1/scalar);
    y *= (1/scalar);
    z *= (1/scalar);
    return *this;
}

bool almost_equal(double x, double y) {
    return std::abs(x - y) < Constants::Epsilon;
}

bool operator==(const Vector3D& lhs, const Vector3D& rhs) {
    return almost_equal(lhs.x, rhs.x) && almost_equal(lhs.y, rhs.y) && almost_equal(lhs.z, rhs.z);
}

bool operator!=(const Vector3D& lhs, const Vector3D& rhs) {
    return !(lhs == rhs);
}

Vector3D operator+(Vector3D lhs, const Vector3D& rhs){
    lhs += rhs;
    return lhs;
}

Vector3D operator-(Vector3D lhs, const Vector3D& rhs){
    lhs -= rhs;
    return lhs;
}

Vector3D operator-(const Vector3D& rhs){
    return -1 * rhs;
}

Vector3D operator*(Vector3D lhs, const Vector3D& rhs){
    lhs *= rhs;
    return lhs;
}

Vector3D operator*(Vector3D lhs, const double scalar) {
    lhs *= scalar;
    return lhs;
}

Vector3D operator*(const double scalar, Vector3D rhs){
    rhs *= scalar;
    return rhs;
}

Vector3D operator/(Vector3D lhs, const double scalar){
    if (scalar == 0)
        throw std::overflow_error("Attempted to divide by Zero\n");
    lhs *= (1/scalar);
    return lhs;
}

Vector3D pow(Vector3D v, const double n){
    v.x = pow(v.x, n);
    v.y = pow(v.y, n);
    v.z = pow(v.z, n);
    return v;
}

double dot(const Vector3D& a, const Vector3D& b){
    double d = ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
    return d;
}

Vector3D cross(const Vector3D& a, const Vector3D& b){
    Vector3D v;
    v.x = ((a.y * b.z) - (b.y * a.z));
    v.y = ((a.z * b.x) - (a.x * b.z));
    v.z = ((a.x * b.y) - (b.x * a.y));
    return v;
}

double norm(const Vector3D& v){
    return sqrt(dot(v,v));
}

Vector3D unit(const Vector3D& v){
    if (norm(v) == 0)
        throw std::overflow_error("Attempted to divide by Zero\n");
    Vector3D vect;
    vect.x = v.x/norm(v);
    vect.y = v.y/norm(v);
    vect.z = v.z/norm(v);
    return vect;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v){
    os << "(" << v.x << " " << v.y << " " << v.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v){
    char a;
    is >> a >> v.x >> v.y >> v.z >> a;
    return is;
}