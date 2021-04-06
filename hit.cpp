#include "hit.h"
#include "material.h"

Hit::Hit(double time, Point3D point, Vector3D normal, std::shared_ptr<Material> material)
    :time{time}, point{point}, normal{normal}, material{material} {}

std::ostream& operator <<(std::ostream& os, const Hit& hit){
    return os << "Hit(time=" << hit.time << ", point=" << hit.point
    << ", normal=" << hit.normal << ", material= " << *(hit.material) << ")";
}

