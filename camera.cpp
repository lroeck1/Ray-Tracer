#include "camera.h"

Camera::Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect)
: position(position), aspect{aspect} {
    Vector3D w = unit(position - target);
    Vector3D u = unit(cross(up, w));
    Vector3D v = cross(w, u);

    double theta = fov * Constants::Pi / 180.0;
    double viewport_height = 2 * std::tan(theta / 2);
    double viewport_width = viewport_height * aspect;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    Point3D image_center = position - w;
    upper_left_corner = image_center - .5 * (horizontal - vertical);
}

Ray Camera::compute_ray(double s, double t) const {
    Point3D point = upper_left_corner + s * horizontal - t * vertical;
    Vector3D direction = unit(point - position);
    return Ray{position, direction};
}

Camera& Camera::operator=(const Camera& rhs){
    position = rhs.position;
    horizontal = rhs. horizontal;
    vertical = rhs.vertical;
    upper_left_corner = rhs.upper_left_corner;
    return *this;
}
