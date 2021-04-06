#pragma once

#include "point3d.h"
#include "ray.h"

class Camera{
public:
    Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect);
    Ray compute_ray(double s, double t) const;
    Camera& operator=(const Camera& rhs);

    Point3D  position;
    Vector3D horizontal, vertical, upper_left_corner;
    double aspect;
};