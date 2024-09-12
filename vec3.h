#ifndef VEC3_H
#define VEC3_H

#include "mat.h"

class Vec3 {
public:
    //Variables
    double e[3];

    //Constructors
    Vec3() : e{0, 0, 0} {};
    Vec3(double x, double y, double z) : e{x, y, z} {};

    //Getters(Get values)
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    //Single vector operations
    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); } //negative values

    double operator[](int i) const { return e[i]; } //return value at index i
    double& operator[](int i) { return e[i]; } //return reference to value at index i

    Vec3& operator+=(const Vec3& v) {  //add scalar to vector
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    Vec3& operator*=(double t) {  //multiply vector by scalar
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    Vec3& operator/=(double t) { //divide vector by scalar
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {   //Verifies if one value of Vec3 is very close to 0
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    static Vec3 random() {  //return random Vec3
        return Vec3(random_double(), random_double(), random_double());
    }

    static Vec3 random(double min, double max) {  //return random Vec3 with values between min and max
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

//Point3 = alias for Vec3 -> geometric calrit in the code
using Point3 = Vec3;


//Vector uti
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) { //output values
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}
inline Vec3 operator/(const Vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) { //Matrix multiplication (dot product)
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
inline Vec3 corss(const Vec3& u, const Vec3& v) { //Cross product
    return Vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

inline Vec3 unit_vector(const Vec3& v) { //Normalize vector
    return v / v.length();
}

inline Vec3 random_in_unit_sphere() {  //Generate random rays until one is the correct direction
    while(true) {
        auto p = Vec3::random(-1, 1);
        if(p.length_squared() < 1)
            return p;
    }
}

inline Vec3 random_unit_vector() {  //Normalizes the random ray
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal) { //check direction of reflected ray
    Vec3 on_unit_sphere = random_unit_vector();
    if(dot(on_unit_sphere, normal) > 0.0) //check if they are in the same hemisphere with the normal
        return on_unit_sphere;
    return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v, n)*n;
    //R(reflected ray) = v(ray_in) + 2 * b(perpendicular from surface to R top)
    //b - scale n by projection of v onto n
    //  = dot product v*n   / n (to normalize)
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);

    //calculate refracted ray on x(perpendicular on the normal) and y(parallel to the normal) axis
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n); 
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;

    return r_out_perp + r_out_parallel;
}

inline Vec3 normalize(const Vec3&v) { return unit_vector(v);}

#endif