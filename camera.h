#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"
#include "hittable.h"
#include "material.h"

using namespace std;

class Camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10; //Number of random samples for each pixel (default)
    int max_depth = 10; //Maximum number of ray bounces into scene (default)

    void render(const Hittable& world) { //Creates output for image file
        initialize();

        cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int j=0;j<image_height;j++) {
            clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
            for(int i=0;i<image_width;i++) {
                Color pixel_color(0, 0, 0);

                for(int sample=0;sample<samples_per_pixel;sample++) { //for every random ray for a pixel
                    Ray r = get_ray(i, j);  //Create ray from origin to rand point 
                    pixel_color += ray_color(r, max_depth, world); //add color from rand point to pixel color
                }
                write_color(cout, pixel_samples_scale * pixel_color); //divide global pixel color to num of rays (avg color)
            }
        }
        clog << "\rDone.            \n";
    }

private:
    int image_height;
    double pixel_samples_scale; //Color scale factor for sum of pixel samples = 1/(num of rand points per pixel)
    Point3 center;      //Camera center
    Point3 pixel00_loc; //Location of pixel (0,0)
    Vec3 pixel_delta_u; //Distance between pixels horizontal (to the right)
    Vec3 pixel_delta_v; //Distance between pixels vertical (below)

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height; //height cannot be less than 1 pixel

        pixel_samples_scale = 1.0 / samples_per_pixel; //instead of dividing each time, make 1 divison, then use it to multiply

        center = Point3(0, 0, 0);

        //Viewport dimensions
        auto focal_length = 1;  //focal_length = distance from camera on the z-axis
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

    Ray get_ray(int i, int j) const {
        //Construct a ray from cam pos and point it at a random point for a pixel
        //Point around the (i, j) location of the pixel

        auto offset = sample_square(); //Get random offset from pixel center
        auto pixel_sample = pixel00_loc    //location of the rand point
                            + ((i + offset.x()) * pixel_delta_u)/*dist on x-axys*/
                            + ((j + offset.y()) * pixel_delta_v)/*dist on y-axis*/;

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin; //dir = destination - origin

        return Ray(ray_origin, ray_direction);
    }

    Vec3 sample_square() const {
        //Return a random point in the unit square of the pixel [-0.5, -0.5]-[0.5, 0.5]
        return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    Color ray_color(const Ray& r, int depth, const Hittable& world) const {   ///Calculate color of ray
        if(depth <= 0) return Color(0, 0, 0); //If ray has no more bounces, return black(null)
        
        HitRecord rec;

        if(world.hit(r, Interval(0.001, infinity), rec)) { //verify if the ray hit an object in 'world'
           
            Ray scattered;
            Color attenuation;
            if(rec.mat->scatter(r, rec, attenuation, scattered)) {  //create reflected ray
                return attenuation * ray_color(scattered, depth-1, world); //return color of hit object
            }
            return Color(0, 0, 0);
        }

        Vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0); //returrn color of bg
        //Linear blend formula: blendedValue = (1-a)*startValue + a*endValue, 0<a<1 
    }

};


#endif