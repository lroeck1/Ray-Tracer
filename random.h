#pragma once

class Vector3D;

double random_double(); // [0.0, 1,0)
double random_double(double min, double max);
Vector3D random_hemisphere(const Vector3D& normal);
Vector3D random_unit_vector();