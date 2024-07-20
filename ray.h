#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
    //Constructors
    Ray() {}
    Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

    //Getters
    const Point3& origin() const {return orig;}
    const Vec3& direction() const {return dir;}

    Point3 at(double t) const { //Function value at t : f(t) = a*t + b
        return orig + t*dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};

#endif