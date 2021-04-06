#include "triangle.h"
#include "constants.h"

Triangle::Triangle(Point3D vertex0, Point3D vertex1, Point3D vertex2, std::shared_ptr<Material> material)
:   vertex0{vertex0}, vertex1{vertex1}, vertex2{vertex2}, material{material}{
    edge1 = vertex1-vertex0;
    edge2 = vertex2-vertex0;
    normal = unit(cross(edge1, edge2));
}

bool Triangle::intersect(const Ray &ray, double &time) const {
    Vector3D pvec = cross(ray.direction, edge2);
    double det = dot(edge1, pvec);

    if ((det > (-1 * Constants::Epsilon)) && (det < Constants::Epsilon)){
        return false;
    }
    double inv_det = 1.0 / det;
    Vector3D tvec = ray.origin - vertex0;

    double u = dot(tvec, pvec) * inv_det;
    if(u < 0.0 || u > 1.0){
        return false;
    }
    Vector3D qvec = cross(tvec, edge1);

    double v = dot(ray.direction, qvec) * inv_det;
    if(v < 0.0 || u + v > 1.0){
        return false;
    }

    double t = inv_det * dot(edge2, qvec);
    if (t > Constants::Epsilon) {
        time = t;
        return true;
    }
    else {
        return false;
    }
}

Hit Triangle::construct_hit(double time, const Ray &ray) {
    Point3D p = ray.at(time);
    if (dot(ray.direction, normal) > 0){
        return Hit{time, p, -normal, material};
    }
    else{
        return Hit{time, p, normal, material};
    }
}

std::pair<double, double> Triangle::uv(const Hit& hit) const{
    Point3D P = hit.point - vertex0;
    double u = dot(P, edge1) / norm(edge1);
    double v = dot(P, edge2) / norm(edge2);
    double mag = (u+v)/2.0;
    return{u/mag, v/mag};
}

std::ostream& operator <<(std::ostream& os, const Triangle& t){
    os << "Triangle(vertex0= " << t.vertex0 << ", vertex1= " << t.vertex1
       << ", vertex2= " << t.vertex2 << ")";
    return os;
}