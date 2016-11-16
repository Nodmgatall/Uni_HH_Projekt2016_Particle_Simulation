/*
 * vec3.hpp
 *
 *  Created on: Nov 16, 2016
 *      Author: benjamin
 */

#ifndef SRC_VEC3_HPP_
#define SRC_VEC3_HPP_

struct vec3 {
    float x, y, z;
    vec3 (float p_x, float p_y, float p_z) : x (p_x), y (p_y), z (p_z) {
    }
    vec3 () {
        x = y = z = 0;
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
    vec3 operator/ (const float &s) {

        return vec3 (x / s, y / s, z / s);
    }
};

#endif /* SRC_VEC3_HPP_ */
