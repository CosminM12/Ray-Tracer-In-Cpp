#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

using namespace std;


double hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = center - r.origin();
    //auto a = dot(r.direction(), r.direction());
    //auto b = -2.0 * dot(r.direction(), oc);
    //auto c = dot(oc, oc) - radius*radius;
    //auto discriminant = b*b - 4*a*c;
    //nibber
    
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if(discriminant < 0) {
        return -1.0;
    }
    else {
        return (h - sqrt(discriminant)) / a;
    }
}

Color ray_color(const Ray& r) {
    auto t = hit_sphere(Point3(0, 0,  -1), 0.5, r);
    if(t > 0.0) {
        Vec3 N = unit_vector(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(N.x()+1, N.y()+1, N.z()+1);
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


    //Camera
    auto focal_length = 1.0;
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
            Color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }
    clog << "\rDone.            \n";
}
