#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);   //Random num in interval [0,1)
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();  //Random num in interval [min, max)
}

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif