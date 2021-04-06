#include "random.h"
#include "vector3d.h"
#include <random>
#include <cmath>
#include "constants.h"

static std::random_device rd;
static std::mt19937 engine{rd()}; // mercium twister

double random_double(){
    // random number between [0.0, 1.0)
    // step 1: random seed
    // static stores the random generator inside the function
    static std::uniform_real_distribution<double> distribution(0,1);
    return distribution(engine);
}

double random_double(double min, double max){
    //random number between [min, max)
    std::uniform_real_distribution<double> distribution(min,max);
    return distribution(engine);
    //return min + (max - min) * random_double();
}

/*Vector3D random_unit_vector() {
    while (true) {
        double x = random_double(-1, 1);
        double y = random_double(-1, 1);
        double z = random_double(-1, 1);
        // if the length is greater than one, reject it and try again
        // randomness won't be true otherwise
        if (x * x + y * y + z * z < 1.0) {
            Vector3D v{x, y, z};
            return unit(v);
        }
    }
}*/

Vector3D random_unit_vector() {
    double theta = random_double(0, Constants::Pi);
    double sin_theta = std::sin(theta);
    double phi = random_double(0, 2*Constants::Pi);
    double x = sin_theta * std::cos(phi);
    double y = sin_theta * std::sin(phi);
    double z = std::cos(theta);
    return Vector3D{x,y,z};
}

Vector3D random_hemisphere(const Vector3D& normal){
    Vector3D vector = random_unit_vector();
    if (dot(vector, normal) > 0.0){
        return vector;
    }
    else {
        return -vector;
    }
}