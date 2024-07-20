#include "mat.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

using namespace std;


Color ray_color(const Ray& r, const Hittable& world) {

    HitRecord rec;
    if(world.hit(r, 0 , infinity, rec)) {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    //Linear blend formula: blendedValue = (1-a)*startValue + a*endValue, 0<a<1
}

int main(int, char**){

    //Image
    auto aspect_ratio = 16.0 / 9.0;
    //int image_width = 400;
    int image_width = 1920;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100.0));

    //Camera
    auto focal_length = 1;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Point3(0, 0, 0);


    //Vectors across viewport edges
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0); //inverted y-axis


    //Delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;


    //Upper-left pixel
    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        //camera-center - distance from camera to viewport plane - half_width - half_height
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        //first pixel -> in the center of the first rectangle of viewport, of lengths du and dv
    

    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j=0;j<image_height;j++) {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
        for(int i=0;i<image_width;i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);
            Color pixel_color = ray_color(r, world);
            write_color(cout, pixel_color);
        }
    }
    clog << "\rDone.            \n";
}
