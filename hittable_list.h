#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "mat.h"
#include "hittable.h"

#include <vector>


class HittableList : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> obj) { 
        add(obj); 
    }

    void add(shared_ptr<Hittable> obj) { 
        objects.push_back(obj); 
    }

    void clear() { 
        objects.clear(); 
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif