#ifndef COLOR_H
#define COLOR_H

#include "mat.h"
#include "vec3.h"

using Color = Vec3;

void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //Translate the [0, 1] component values to byte range [0, 255];
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif