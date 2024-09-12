#include "mat.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

using namespace std;

int main(int, char**){

    //World
    HittableList world;
    //world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    //world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100.0));
    
    //Materials
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2));

    //Objects
    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


    //Camera settings
    Camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}
