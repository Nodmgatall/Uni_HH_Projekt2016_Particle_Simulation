/*
 * vec3.hpp
 *
 *  Created on: Nov 16, 2016
 *      Author: benjamin
 */

#ifndef SRC_VEC3_HPP_
#define SRC_VEC3_HPP_

template <typename T>
struct vec3;

typedef vec3<float> vec3f;
typedef vec3<long>  vec3l;

template <typename T>
struct vec3 {
    T x, y, z;
    vec3 (T p_x, T p_y, T p_z) : x (p_x), y (p_y), z (p_z) {
    }
    vec3 () {
        x = y = z = 0;
    }
    vec3 (T v) {
        x = y = z = v;
    }
    template <typename U>
    vec3 (vec3<U> v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    vec3 operator+ (const vec3 &other) {
        return vec3 (x + other.x, y + other.y, z + other.z);
    }
    vec3 operator- (const vec3 &other) {
        return vec3 (x - other.x, y - other.y, z - other.z);
    }
    vec3 operator* (const vec3 &other) {
        return vec3 (x * other.x, y * other.y, z * other.z);
    }
    vec3 operator/ (const T &s) {
        return vec3 (x / s, y / s, z / s);
    }
    static vec3 max (const vec3 &a, const vec3 &b) {
        return vec3 (a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
    }
};

#endif /* SRC_VEC3_HPP_ */
