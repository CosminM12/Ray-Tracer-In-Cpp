#ifndef HITTABLE_H
#define HITTABLE_H

#include "mat.h"

class HitRecord {
public:
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        //sets the hit record normal vector

        front_face = dot(r.direction(), outward_normal) < 0;  // checks if the ray's direction is facing the hit point in the same direction as the normal vector
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif