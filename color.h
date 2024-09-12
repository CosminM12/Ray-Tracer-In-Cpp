#ifndef COLOR_H
#define COLOR_H

#include "mat.h"
#include "vec3.h"
#include "interval.h"

using Color = Vec3;

inline double linear_to_gamma(double linear_component) {
    if(linear_component > 0)
        return sqrt(linear_component);
    
    return 0;
}

void write_color(std::ostream& out, const Color& pixel_color) {
    //Get pixel colors
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply gamma correction to the color components
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Clamp the color components to the [0, 1] range
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));


    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif