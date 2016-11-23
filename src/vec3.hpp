/*
 * vec3.hpp
 *
 *  Created on: Nov 16, 2016
 *      Author: benjamin
 */

#ifndef SRC_VEC3_HPP_
#define SRC_VEC3_HPP_

#include <math.h>

template <typename T>
struct vec3;

typedef vec3<float> vec3f;
typedef vec3<long>  vec3l;

template <typename T>
struct vec3 {
    T x, y, z;
    inline vec3 (T p_x, T p_y, T p_z) : x (p_x), y (p_y), z (p_z) {
    }
    inline vec3 () {
        x = y = z = 0;
    }
    inline vec3 (T v) {
        x = y = z = v;
    }
    template <typename U>
    inline vec3 (vec3<U> v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    inline vec3 operator+ (const vec3 &other) {
        return vec3 (x + other.x, y + other.y, z + other.z);
    }
    inline vec3 operator+= (const vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    inline vec3 operator+= (const T &s) {
        x += s;
        y += s;
        z += s;
        return *this;
    }
    inline vec3 operator- (const vec3 &other) {
        return vec3 (x - other.x, y - other.y, z - other.z);
    }
    inline vec3 operator- (const T &s) {
        return vec3 (x - s, y - s, z - s);
    }
    inline vec3 operator* (const vec3 &other) {
        return vec3 (x * other.x, y * other.y, z * other.z);
    }
    inline vec3 operator/ (const T &s) {
        return vec3 (x / s, y / s, z / s);
    }
    inline vec3 operator/ (const vec3 &other) {
        return vec3 (x / other.x, y / other.y, z / other.z);
    }
    inline static vec3 max (const vec3 &a, const vec3 &b) {
        return vec3 (a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
    }
    inline static vec3 min (const vec3 &a, const vec3 &b) {
        return vec3 (a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z);
    }
    inline T length () {
        return sqrt (x * x + y * y + z * z);
    }
};

#endif /* SRC_VEC3_HPP_ */
