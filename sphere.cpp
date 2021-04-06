#include "sphere.h"
#include "ray.h"
#include "material.h"
#include <cmath>

Sphere::Sphere(Point3D center, double radius, std::shared_ptr<Material> material)
    : center{center}, radius{radius}, material{material}{}

bool Sphere::intersect(const Ray &ray, double& time) const {
    auto CP = center - ray.origin;
    double R = dot(CP, ray.direction);
    double q2 = dot(CP, CP) - R * R;
    if (q2 > radius * radius) {
        return false;
    }

    // hit
    double h = std::sqrt(radius * radius - q2); // t = R +/- h
    if ((R - h) > Constants::Epsilon) {
        // Outside sphere, if time is positive and far enough away
        time = R - h;
        return true;
    }
    else if ((R + h) > Constants::Epsilon) { // time > Epsilon
        // Inside sphere, time is positive, and far enough away
        time = R + h;
        return true;
    }
    else { // all cases of sphere surface is too close
        return false;
    }
}

std::ostream& operator <<(std::ostream& os, const Sphere& s){
    os << "Sphere(center=" << s.center << ", radius=" << s.radius
       << ")";
    return os;
}

Hit Sphere::construct_hit(double time, const Ray& ray) {
    Point3D p = ray.at(time);
    Vector3D normal = unit(p-center);
    Hit h{time, p, normal, material};
    return h;
}

std::pair<double, double> Sphere::uv(const Hit &hit) const {
    double theta = std::acos(hit.normal.z);
    double phi = std::atan2(hit.normal.y, hit.normal.x); // [-pi, pi]

    double u = 0.5 + phi / (2*Constants::Pi); // [0, 1]
    double v = theta / Constants::Pi;
    return {u, v};
}