#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

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

inline Vec3 normalize(const Vec3&v) { return unit_vector(v);}

#endif