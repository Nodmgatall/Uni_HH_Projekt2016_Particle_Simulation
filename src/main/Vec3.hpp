/*
 * Vec3.hpp
 *
 *  Created on: Nov 16, 2016
 *      Author: benjamin
 */

#ifndef SRC_VEC3_HPP_
#define SRC_VEC3_HPP_

#include <math.h>
#include <ostream>

template <typename T>
struct Vec3 {
    T x, y, z;
    inline Vec3 (T p_x, T p_y, T p_z) : x (p_x), y (p_y), z (p_z) {
    }
    inline Vec3 () {
        x = y = z = 0;
    }
    inline Vec3 (T v) {
        x = y = z = v;
    }
    template <typename U>
    inline Vec3 (Vec3<U> v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    inline Vec3 operator+ (const Vec3 &other) {
        return Vec3 (x + other.x, y + other.y, z + other.z);
    }
    inline Vec3 operator+= (const Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    inline Vec3 operator+= (const T &s) {
        x += s;
        y += s;
        z += s;
        return *this;
    }
    inline Vec3 operator- (const Vec3 &other) {
        return Vec3 (x - other.x, y - other.y, z - other.z);
    }
    inline Vec3 operator- (const T &s) {
        return Vec3 (x - s, y - s, z - s);
    }
    inline Vec3 operator* (const Vec3 &other) {
        return Vec3 (x * other.x, y * other.y, z * other.z);
    }
    inline Vec3 operator/ (const T &s) {
        return Vec3 (x / s, y / s, z / s);
    }
    inline Vec3 operator/ (const Vec3 &other) {
        return Vec3 (x / other.x, y / other.y, z / other.z);
    }
    inline bool operator== (const Vec3 &other) {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }
    inline bool operator!= (const Vec3 &other) {
        return (x != other.x) || (y != other.y) || (z != other.z);
    }
    inline static Vec3 max (const Vec3 &a, const Vec3 &b) {
        return Vec3 (a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
    }
    inline static Vec3 min (const Vec3 &a, const Vec3 &b) {
        return Vec3 (a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z);
    }
    inline T length () {
        return sqrt (x * x + y * y + z * z);
    }
    inline friend std::ostream &operator<< (std::ostream &stream, const Vec3 vec) {
        return stream << "Vec3(" << vec.x << "," << vec.y << "," << vec.z << ")";
    }
};

typedef Vec3<float> Vec3f;
typedef Vec3<long>  Vec3l;

extern const Vec3f g_vec3f_0;
extern const Vec3l g_vec3l_0;
#endif /* SRC_Vec3_HPP_ */
