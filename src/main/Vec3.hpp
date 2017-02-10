/*
 * Vec3.hpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#ifndef SRC_VEC3_HPP_
#define SRC_VEC3_HPP_
#include "DataType.hpp"
#include "tools/Debug.hpp"
#include <iostream>
#include <istream>
#include <math.h>
#include <ostream>
#include <sstream>
template <typename T>
struct Vec3 {
    T x, y, z;
    /**
     * constructor
     */
    inline Vec3<T> (T p_x, T p_y, T p_z) : x (p_x), y (p_y), z (p_z) {
    }
    /**
     * constructor initialize all values with 0
     */
    inline Vec3<T> () {
        x = y = z = 0;
    }
    /**
     * constructor initialize all 3 dimensions with the same (given) value
     */
    inline Vec3<T> (T v) {
        x = y = z = v;
    }
    /**
     * copy-constructor
     */
    template <typename U>
    inline Vec3<T> (Vec3<U> v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    /**
     * adds two vectors by component
     */
    inline Vec3<T> operator+ (const Vec3<T>& other) {
        return Vec3<T> (x + other.x, y + other.y, z + other.z);
    }
    /**
     * adds two vectors into the current one and return the current vector
     */
    inline Vec3<T> operator+= (const Vec3<T>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    /**
     * add an scalar to the current vector and return the current vector
     */
    inline Vec3<T> operator+= (const T& s) {
        x += s;
        y += s;
        z += s;
        return *this;
    }
    /**
     * substract an other vector from the current one and return the current one
     */
    inline Vec3<T> operator- (const Vec3<T>& other) {
        return Vec3<T> (x - other.x, y - other.y, z - other.z);
    }
    /**
     * substracts an scalar from the current vector and resturn the current vecctor
     */
    inline Vec3<T> operator- (const T& s) {
        return Vec3<T> (x - s, y - s, z - s);
    }
    /**
     * multiplication by component. return a new vector.
     */
    inline Vec3<T> operator* (const Vec3<T>& other) {
        return Vec3<T> (x * other.x, y * other.y, z * other.z);
    }
    /**
     * divide current vector through an skalar
     */
    inline Vec3<T> operator/ (const T& s) {
        return Vec3<T> (x / s, y / s, z / s);
    }
    /**
     * devides the current vector component-wise through the other vector. return a new vector with
     * the result
     */
    inline Vec3<T> operator/ (const Vec3<T>& other) {
        return Vec3<T> (x / other.x, y / other.y, z / other.z);
    }
    /**
     * compares the two given vectors for equality
     */
    inline friend bool operator== (const Vec3<T>& left, const Vec3<T>& right) {
        return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
    }
    /**
     * compares the two vectors for inequality
     */
    inline friend bool operator!= (const Vec3<T>& left, const Vec3<T>& right) {
        return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
    }
    /**
     * returns the component-wise maxyimum of both input vectors as a new vector
     */
    inline static Vec3<T> max (const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T> (a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z);
    }
    /**
     * returns the component-wise mimimum of both input vectors as a new vector
     */
    inline static Vec3<T> min (const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T> (a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z);
    }
    /**
     * return the length of an vector
     */
    inline T length () {
        return sqrt (x * x + y * y + z * z);
    }
    /**
     * append this vector to the given stream. (as string representation)
     */
    inline friend std::ostream& operator<< (std::ostream& stream, const Vec3<T>& vec) {
        return stream << "Vec(" << vec.x << "," << vec.y << "," << vec.z << ")";
    }
    /**
     * loads the vector from the given (text) stream
     */
    inline friend std::istream& operator>> (std::istream& stream, Vec3<T>& vec) {
        if (stream.peek () == 'V') {
            stream.ignore ();
            if (stream.peek () == 'e') {
                stream.ignore ();
                if (stream.peek () == 'c') {
                    stream.ignore ();
                }
            }
        }
        while ((stream.peek () == ' ') || (stream.peek () == '(') || (stream.peek () == '[')) {
            stream.ignore ();
        }
        stream >> vec.x;
        while ((stream.peek () == ' ') || (stream.peek () == '/') || (stream.peek () == '|') || ((char) stream.peek () == ',')) {
            stream.ignore ();
        }
        stream >> vec.y;
        while ((stream.peek () == ' ') || (stream.peek () == '/') || (stream.peek () == '|') || ((char) stream.peek () == ',')) {
            stream.ignore ();
        }
        stream >> vec.z;
        while ((stream.peek () == ' ') || (stream.peek () == ')') || (stream.peek () == ']')) {
            stream.ignore ();
        }
        return stream;
    }
    /**
     * rotates this vector around the x axis by the given angle in radians
     */
    inline Vec3<T> rotateX (T alpha) {
        return Vec3<T> (x, y * cos (alpha) - z * sin (alpha), y * sin (alpha) + z * cos (alpha));
    }
    /**
     * rotates this vector around the y axis by the given angle in radians
     */
    inline Vec3<T> rotateY (T alpha) {
        return Vec3<T> (x * cos (alpha) + z * sin (alpha), y, -x * sin (alpha) + z * cos (alpha));
    }
    /**
     * rotates this vector around the z axis by the given angle in radians
     */
    inline Vec3<T> rotateZ (T alpha) {
        return Vec3<T> (x * cos (alpha) - y * sin (alpha), x * sin (alpha) + y * cos (alpha), z);
    }
};
/**
 * an vector with the data_type defined in the 'DataType-header
 */
typedef Vec3<data_type> Vec3f;
/**
 * an vector containing long values
 */
typedef Vec3<long> Vec3l;
/**
 * an global vector containing only 0 for all three components
 */
extern const Vec3f g_vec3f_0;
/**
 * an global vector containing only 0 for all three components
 */
extern const Vec3l g_vec3l_0;
#endif /* SRC_Vec3_HPP_ */
