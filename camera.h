#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"
#include "hittable.h"

using namespace std;

class Camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;

    void render(const Hittable& world) {
        initialize();

        cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int j=0;j<image_height;j++) {
            clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
            for(int i=0;i<image_width;i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                Ray r(center, ray_direction);
                Color pixel_color = ray_color(r, world);
                write_color(cout, pixel_color);
            }
        }
        clog << "\rDone.            \n";
    }

private:
    int image_height;   //Rendered image height
    Point3 center;      //Camera center
    Point3 pixel00_loc; //Location of pixel (0,0)
    Vec3 pixel_delta_u; //Offset to pixel to the right
    Vec3 pixel_delta_v; //Offfset to pixel below

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = Point3(0, 0, 0);

        //Viewport dimensions
        auto focal_length = 1;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        //Vectors across the horizontal and vertical axis
        auto viewport_u = Vec3(viewport_width, 0, 0);
        auto viewport_v = Vec3(0, -viewport_height, 0); //inverted y-axis

        //Horizontal and vertical delta vectors between pixels
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        //Upper left pixel location
        auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            //camera-center - distance from camera to viewport plane - half_width - half_height
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
            //first pixel -> in the center of the first rectangle of viewport, of lengths du and dv
    }

    Color ray_color(const Ray& r, const Hittable& world) const {
        HitRecord rec;
        if(world.hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        Vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
        //Linear blend formula: blendedValue = (1-a)*startValue + a*endValue, 0<a<1 
    }

};


#endif