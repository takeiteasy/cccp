/* paul/paul_math.h -- https://github.com/takeiteasy/paul

 Copyright (C) 2024  George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#ifndef PAUL_MATH_HEADER
#define PAUL_MATH_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#ifndef PAUL_MATH_NO_PRINT
#include <stdio.h>
#endif
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <tgmath.h>
#ifdef __cplusplus
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#else
#include <stdbool.h>
#endif

#if !defined(__cplusplus) && (!defined(__clang__) && !defined(__GNUC__))
#define PAUL_MATH_NO_MATRICES
#endif

#ifndef __has_extension
#define __has_extension(x) 0
#endif

#if defined(__cpluscplus) || __STDC_VERSION__ < 201112L || !__has_extension(c_generic_selections)
#define PAUL_NO_GENERICS
#endif

#ifndef PAUL_MATH_FLOAT_EPSILON
#define PAUL_MATH_FLOAT_EPSILON 0.000001f
#endif

#if __cplusplus || __STDC_VERSION__ >= 202311L
#define CONST constexpr
#else
#define CONST const
#endif
static CONST float tau = M_2_PI;
static CONST float phi = 1.61803398874989484820f;
static CONST float inv_phi = 0.61803398874989484820f;
static CONST float euler = 2.71828182845904523536f;
static CONST float epsilon = PAUL_MATH_FLOAT_EPSILON;

#ifdef __cplusplus
static inline template<typename T> min(T a, T b) {
    return a < b ? a : b;
}

static inline template<typename T> max(T a, T b) {
    return a > b ? a : b;
}

static inline template<typename T> clamp(T value, T minval, T maxval) {
    return value < minval ? minval : (value > maxval ? maxval : value);
}

static inline template<typename T> to_degrees(T radians) {
    return radians * (180.f / M_PI);
}

static inline template<typename T> to_radians(T degrees) {
    return degrees * (M_PI / 180.f);
}
#else
#if __STDC_VERSION__ < 202311L
#if defined(__clang__) || defined(__GNUC__)
#ifndef typeof
#define typeof(x) __typeof__((x))
#endif
#else
#define PAUL_NO_TYPEOF
#endif
#endif

#ifndef PAUL_NO_TYPEOF
#define min(a, b)           \
    ({typeof (a) _a = (a);  \
      typeof (a) _b = (b);  \
      _a < _b ? _a : _b; })

#define max(a, b)           \
    ({typeof (a) _a = (a);  \
      typeof (a) _b = (b);  \
      _a > _b ? _a : _b; })

#define clamp(value, minval, maxval)       \
    ({typeof (value) _value  = (value);    \
      typeof (value) _minval = (minval);   \
      typeof (value) _maxval = (maxval);   \
      _value < _minval ? _minval : (_value > _maxval ? _maxval : _value); })

#define to_degrees(radians)                     \
    ({typeof (radians) _radians = (radians);    \
      _radians * (180.f / M_PI); })

#define to_radians(degrees)                     \
    ({typeof (degrees) _degrees = (degrees);    \
      _degrees * (M_PI / 180.f); })

#define remap(x, in_min, in_max, out_min, out_max)  \
    ({typeof (x) _x = (x);                          \
      typeof (in_min) _in_min = (in_min);           \
      typeof (in_max) _in_max = (in_max);           \
      typeof (out_min) _out_min = (out_min);        \
      typeof (out_max) _out_max = (out_max);        \
      _out_min + (_x - _in_min) * (_out_max - _out_min) / (_in_max - _in_min); })
#else
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define clamp(value, minval, maxval) \
    ((value) < (minval) ? (minval) : ((value) > (maxval) ? (maxval) : (value)))

#define to_degrees(radians) ((radians) * (180.f / M_PI))
#define to_radians(degrees) ((degrees) * (M_PI / 180.f))

#define remap(x, in_min, in_max, out_min, out_max) \
    ((out_min) + ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)))
#endif // PAUL_NO_TYPEOF
#endif

#define bytes(n)         (n)
#define kilobytes(n)     (n << 10)
#define megabytes(n)     (n << 20)
#define gigabytes(n)     (((uint64_t)n) << 30)
#define terabytes(n)     (((uint64_t)n) << 40)

#define thousand(n)      ((n) * 1000)
#define million(n)       ((n) * 1000000)
#define billion(n)       ((n) * 1000000000LL)

#define nanoseconds(ms)  ((uint64_t)ms / 1000000LL)
#define microseconds(ms) (ms / 1000)
#define milliseconds(n)  (n)
#define seconds(n)       (n * 1000)
#define minutes(n)       ((uint64_t)n * 60000LL)
#define hours(n)         ((uint64_t)n * 3600000LL)
#define days(n)          ((uint64_t)n * 86400000LL)
#define weeks(n)         ((uint64_t)n * 604800000LL)

#define __PAUL_MATH_TYPES \
    X(2)                  \
    X(3)                  \
    X(4)

#ifdef __cplusplus
template<typename T, int N> class vec {
protected:
    std::array<T, N> data;
public:
    vec(): data{} {}
    vec(std::initializer_list<T> init) { std::copy(init.begin(), init.end(), data.begin()); }
    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const {
        if (index < 0 || index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    int size() const { return N; }
};

#define _VEC_OPERATORS(T, N, S)                                                              \
    vec##S operator+(T scalar) const                                                         \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] += scalar;                                                        \
        return result;                                                                       \
    }                                                                                        \
    vec##S operator+(const vec##S &other) const                                              \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] += other.data[i];                                                 \
        return result;                                                                       \
    }                                                                                        \
    void operator+=(T scalar)                                                                \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] += scalar;                                                               \
    }                                                                                        \
    void operator+=(const vec##S &other)                                                     \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] += other.data[i];                                                        \
    }                                                                                        \
    vec##S operator-(T scalar) const                                                         \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] -= scalar;                                                        \
        return result;                                                                       \
    }                                                                                        \
    vec##S operator-(const vec##S &other) const                                              \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] -= other.data[i];                                                 \
        return result;                                                                       \
    }                                                                                        \
    void operator-=(T scalar)                                                                \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] -= scalar;                                                               \
    }                                                                                        \
    void operator-=(const vec##S &other)                                                     \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] -= other.data[i];                                                        \
    }                                                                                        \
    vec##S operator*(T scalar) const                                                         \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] *= scalar;                                                        \
        return result;                                                                       \
    }                                                                                        \
    vec##S operator*(const vec##S &other) const                                              \
    {                                                                                        \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] *= other.data[i];                                                 \
        return result;                                                                       \
    }                                                                                        \
    void operator*=(T scalar)                                                                \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] *= scalar;                                                               \
    }                                                                                        \
    void operator*=(const vec##S &other)                                                     \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            data[i] *= other.data[i];                                                        \
    }                                                                                        \
    vec##S operator/(T scalar) const                                                         \
    {                                                                                        \
        if (scalar == 0.f)                                                                   \
            throw std::invalid_argument("Division by zero");                                 \
        vec##S result = *this;                                                               \
        for (int i = 0; i < N; i++)                                                          \
            result.data[i] /= scalar;                                                        \
        return result;                                                                       \
    }                                                                                        \
    void operator/=(T scalar)                                                                \
    {                                                                                        \
        if (scalar == 0.f)                                                                   \
            throw std::invalid_argument("Division by zero");                                 \
        for (int i = 0; i < N; i++)                                                          \
            data[i] /= scalar;                                                               \
    }                                                                                        \
    bool operator==(const vec##S &other) const                                               \
    {                                                                                        \
        for (int i = 0; i < N; i++)                                                          \
            if (data[i] != other.data[i])                                                    \
                return false;                                                                \
        return true;                                                                         \
    }                                                                                        \
    vec##S &operator=(const vec##S &other)                                                   \
    {                                                                                        \
        if (this != &other)                                                                  \
            data = other.data;                                                               \
        return *this;                                                                        \
    }                                                                                        \
    vec##S &operator=(std::initializer_list<T> init)                                         \
    {                                                                                        \
        if (init.size() != N)                                                                \
            throw std::invalid_argument("Initializer list size does not match vector size"); \
        std::copy(init.begin(), init.end(), data.begin());                                   \
        return *this;                                                                        \
    }

template<typename T> struct _Proxy {
private:
    T *value;
public:
    _Proxy(T *v): value(v) {}
    operator T() const { return *value; }
    _Proxy &operator=(T a) {
        *value = a;
        return *this;
    }
};

class vec2: public vec<float, 2> {
public:
    _Proxy<float> x = _Proxy<float>(&data[0]);
    _Proxy<float> y = _Proxy<float>(&data[1]);
    vec2() {}
    vec2(float x, float y = 0.f) { data = {x, y}; }
    _VEC_OPERATORS(float, 2, 2)
};

class vec2i: public vec<int, 2> {
public:
    _Proxy<int> x = _Proxy<int>(&data[0]);
    _Proxy<int> y = _Proxy<int>(&data[1]);
    vec2i() {}
    vec2i(int x, int y = 0) { data = {x, y}; }
    _VEC_OPERATORS(int, 2, 2i)
};

class vec3: public vec<float, 3> {
public:
    _Proxy<float> x = _Proxy<float>(&data[0]);
    _Proxy<float> y = _Proxy<float>(&data[1]);
    _Proxy<float> z = _Proxy<float>(&data[2]);
    vec3() {}
    vec3(float x, float y = 0.f, float z = 0.f) { data = {x, y, z}; }
    _VEC_OPERATORS(float, 3, 3)
};

class vec3i: public vec<int, 3> {
public:
    _Proxy<int> x = _Proxy<int>(&data[0]);
    _Proxy<int> y = _Proxy<int>(&data[1]);
    _Proxy<int> z = _Proxy<int>(&data[2]);
    vec3i() {}
    vec3i(int x, int y = 0, int z = 0) { data = {x, y, z}; }
    _VEC_OPERATORS(int, 3, 3i)
};

class vec4: public vec<float, 4> {
public:
    _Proxy<float> x = _Proxy<float>(&data[0]);
    _Proxy<float> y = _Proxy<float>(&data[1]);
    _Proxy<float> z = _Proxy<float>(&data[2]);
    _Proxy<float> w = _Proxy<float>(&data[3]);
    vec4() {}
    vec4(float x, float y = 0.f, float z = 0.f, float w = 0.f) { data = {x, y, z, w}; }
    _VEC_OPERATORS(float, 4, 4)
};

class vec4i: public vec<int, 4> {
public:
    _Proxy<int> x = _Proxy<int>(&data[0]);
    _Proxy<int> y = _Proxy<int>(&data[1]);
    _Proxy<int> z = _Proxy<int>(&data[2]);
    _Proxy<int> w = _Proxy<int>(&data[3]);
    vec4i() {}
    vec4i(int x, int y = 0, int z = 0, int w = 0) { data = {x, y, z, w}; }
    _VEC_OPERATORS(float, 4, 4i)
};

template<typename T, int N> class mat {
protected:
    std::array<std::array<T, N>, N> data;
public:
    mat() {
        for (int i = 0; i < N; i++)
            data[i].fill(0);
    }
    mat(std::initializer_list<std::initializer_list<T>> init) {
        if (init.size() != N)
            throw std::invalid_argument("Initializer list size does not match matrix size");
        int i = 0;
        for (const auto &row : init) {
            if (row.size() != N)
                throw std::invalid_argument("Row size does not match matrix size");
            std::copy(row.begin(), row.end(), data[i++].begin());
        }
    }
    std::array<T, N> &operator[](int index) {
        if (index < 0 || index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    const std::array<T, N> &operator[](int index) const {
        if (index < 0 || index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    int size() const { return N; }
};

#define _MAT_OPERATORS(T, N, S)                                                                 \
    mat##S operator+(T scalar) const                                                            \
    {                                                                                           \
        mat##S result = *this;                                                                  \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                result.data[i][j] += scalar;                                                    \
        return result;                                                                          \
    }                                                                                           \
    mat##S operator+(const mat##S &other) const                                                 \
    {                                                                                           \
        mat##S result = *this;                                                                  \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                result.data[i][j] += other.data[i][j];                                          \
        return result;                                                                          \
    }                                                                                           \
    void operator+=(T scalar)                                                                   \
    {                                                                                           \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                data[i][j] += scalar;                                                           \
    }                                                                                           \
    void operator+=(const mat##S &other)                                                        \
    {                                                                                           \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                data[i][j] += other.data[i][j];                                                 \
    }                                                                                           \
    mat##S operator-(T scalar) const                                                            \
    {                                                                                           \
        mat##S result = *this;                                                                  \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                result.data[i][j] -= scalar;                                                    \
        return result;                                                                          \
    }                                                                                           \
    mat##S operator-(const mat##S &other) const                                                 \
    {                                                                                           \
        mat##S result = *this;                                                                  \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                result.data[i][j] -= other.data[i][j];                                          \
        return result;                                                                          \
    }                                                                                           \
    void operator-=(T scalar)                                                                   \
    {                                                                                           \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                data[i][j] -= scalar;                                                           \
    }                                                                                           \
    void operator-=(const mat##S &other)                                                        \
    {                                                                                           \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                data[i][j] -= other.data[i][j];                                                 \
    }                                                                                           \
    mat##S operator*(const mat##S &other) const                                                 \
    {                                                                                           \
        return mul(other);                                                                      \
    }                                                                                           \
    mat##S &operator*=(const mat##S &other)                                                     \
    {                                                                                           \
        *this = mul(other);                                                                     \
        return *this;                                                                           \
    }                                                                                           \
    bool operator==(const mat##S &other) const                                                  \
    {                                                                                           \
        for (int i = 0; i < N; i++)                                                             \
            for (int j = 0; j < N; j++)                                                         \
                if (data[i][j] != other.data[i][j])                                             \
                    return false;                                                               \
        return true;                                                                            \
    }                                                                                           \
    mat##S &operator=(const mat##S &other)                                                      \
    {                                                                                           \
        if (this != &other)                                                                     \
            data = other.data;                                                                  \
        return *this;                                                                           \
    }                                                                                           \
    mat##S &operator=(std::initializer_list<std::initializer_list<T>> init)                     \
    {                                                                                           \
        if (init.size() != N)                                                                   \
            throw std::invalid_argument("Initializer list size does not match matrix size");    \
        int i = 0;                                                                              \
        for (const auto &row : init) {                                                          \
            if (row.size() != N)                                                                \
                throw std::invalid_argument("Row size does not match matrix size");             \
            std::copy(row.begin(), row.end(), data[i++].begin());                               \
        }                                                                                       \
        return *this;                                                                           \
    }

class mat2: public mat<float, 2> {
    mat2 mul(const mat2 &other) const {
        return mat2(data[0][0] * other.data[0][0] + data[0][1] * other.data[1][0],
                    data[0][0] * other.data[0][1] + data[0][1] * other.data[1][1],
                    data[1][0] * other.data[0][0] + data[1][1] * other.data[1][0],
                    data[1][0] * other.data[0][1] + data[1][1] * other.data[1][1]);
    }
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    mat2() {}
    mat2(float a, float b, float c, float d) {
        data[0][0] = a; data[0][1] = b;
        data[1][0] = c; data[1][1] = d;
    }
    _MAT_OPERATORS(float, 2, 2);
};

class mat3: public mat<float, 3> {
    mat3 mul(const mat3 &other) const {
        return mat3(data[0][0] * other.data[0][0] + data[0][1] * other.data[1][0] + data[0][2] * other.data[2][0],
                    data[0][0] * other.data[0][1] + data[0][1] * other.data[1][1] + data[0][2] * other.data[2][1],
                    data[0][0] * other.data[0][2] + data[0][1] * other.data[1][2] + data[0][2] * other.data[2][2],
                    data[1][0] * other.data[0][0] + data[1][1] * other.data[1][0] + data[1][2] * other.data[2][0],
                    data[1][0] * other.data[0][1] + data[1][1] * other.data[1][1] + data[1][2] * other.data[2][1],
                    data[1][0] * other.data[0][2] + data[1][1] * other.data[1][2] + data[1][2] * other.data[2][2],
                    data[2][0] * other.data[0][0] + data[2][1] * other.data[1][0] + data[2][2] * other.data[2][0],
                    data[2][0] * other.data[0][1] + data[2][1] * other.data[1][1] + data[2][2] * other.data[2][1],
                    data[2][0] * other.data[0][2] + data[2][1] * other.data[1][2] + data[2][2] * other.data[2][2]);
    }
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m02 = _Proxy<float>(&data[0][2]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    _Proxy<float> m12 = _Proxy<float>(&data[1][2]);
    _Proxy<float> m20 = _Proxy<float>(&data[2][0]);
    _Proxy<float> m21 = _Proxy<float>(&data[2][1]);
    _Proxy<float> m22 = _Proxy<float>(&data[2][2]);
    mat3() {}
    mat3(float a, float b, float c,
         float d, float e, float f,
         float g, float h, float i) {
        data[0][0] = a; data[0][1] = b; data[0][2] = c;
        data[1][0] = d; data[1][1] = e; data[1][2] = f;
        data[2][0] = g; data[2][1] = h; data[2][2] = i;
    }
    _MAT_OPERATORS(float, 3, 3);
};

class mat4: public mat<float, 4> {
    mat4 mul(const mat4 &other) const {
        return mat4(data[0][0] * data[0][0] + data[0][1] * data[0][1] + data[2][0] * data[0][2] + data[3][0] * data[0][3],
                    data[0][0] * data[1][0] + data[0][1] * data[1][1] + data[2][0] * data[1][2] + data[3][0] * data[1][3],
                    data[0][0] * data[2][0] + data[0][1] * data[2][1] + data[2][0] * data[2][2] + data[3][0] * data[2][3],
                    data[0][0] * data[3][0] + data[0][1] * data[3][1] + data[2][0] * data[3][2] + data[3][0] * data[3][3],
                    data[0][1] * data[0][0] + data[1][1] * data[0][1] + data[2][1] * data[0][2] + data[3][1] * data[0][3],
                    data[0][1] * data[1][0] + data[1][1] * data[1][1] + data[2][1] * data[1][2] + data[3][1] * data[1][3],
                    data[0][1] * data[2][0] + data[1][1] * data[2][1] + data[2][1] * data[2][2] + data[3][1] * data[2][3],
                    data[0][1] * data[3][0] + data[1][1] * data[3][1] + data[2][1] * data[3][2] + data[3][1] * data[3][3],
                    data[0][2] * data[0][0] + data[1][2] * data[0][1] + data[2][2] * data[0][2] + data[3][2] * data[0][3],
                    data[0][2] * data[1][0] + data[1][2] * data[1][1] + data[2][2] * data[1][2] + data[3][2] * data[1][3],
                    data[0][2] * data[2][0] + data[1][2] * data[2][1] + data[2][2] * data[2][2] + data[3][2] * data[2][3],
                    data[0][2] * data[3][0] + data[1][2] * data[3][1] + data[2][2] * data[3][2] + data[3][2] * data[3][3],
                    data[0][3] * data[0][0] + data[1][3] * data[0][1] + data[2][3] * data[0][2] + data[3][3] * data[0][3],
                    data[0][3] * data[1][0] + data[1][3] * data[1][1] + data[2][3] * data[1][2] + data[3][3] * data[1][3],
                    data[0][3] * data[2][0] + data[1][3] * data[2][1] + data[2][3] * data[2][2] + data[3][3] * data[2][3],
                    data[0][3] * data[3][0] + data[1][3] * data[3][1] + data[2][3] * data[3][2] + data[3][3] * data[3][3]);
    }
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m02 = _Proxy<float>(&data[0][2]);
    _Proxy<float> m03 = _Proxy<float>(&data[0][3]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    _Proxy<float> m12 = _Proxy<float>(&data[1][2]);
    _Proxy<float> m13 = _Proxy<float>(&data[1][3]);
    _Proxy<float> m20 = _Proxy<float>(&data[2][0]);
    _Proxy<float> m21 = _Proxy<float>(&data[2][1]);
    _Proxy<float> m22 = _Proxy<float>(&data[2][2]);
    _Proxy<float> m23 = _Proxy<float>(&data[2][3]);
    _Proxy<float> m30 = _Proxy<float>(&data[3][0]);
    _Proxy<float> m31 = _Proxy<float>(&data[3][1]);
    _Proxy<float> m32 = _Proxy<float>(&data[3][2]);
    _Proxy<float> m33 = _Proxy<float>(&data[3][3]);
    mat4() {}
    mat4(float a, float b, float c, float d,
         float e, float f, float g, float h,
         float i, float j, float k, float l,
         float m, float n, float o, float p) {
        data[0][0] = a; data[0][1] = b; data[0][2] = c; data[0][3] = d;
        data[1][0] = e; data[1][1] = f; data[1][2] = g; data[1][3] = h;
        data[2][0] = i; data[2][1] = j; data[2][2] = k; data[2][3] = l;
        data[3][0] = m; data[3][1] = n; data[3][2] = o; data[3][3] = p;
    }
    _MAT_OPERATORS(float, 4, 4);
};
#else
#define vector(N) __attribute__((ext_vector_type((N))))
#define X(SZ) \
    typedef float vec##SZ vector(SZ);
__PAUL_MATH_TYPES
#undef X
#endif // __cplusplus

#define X(SZ)                                           \
    vec##SZ vec##SZ##_zero(void);                       \
    bool vec##SZ##_is_zero(vec##SZ);                    \
    float vec##SZ##_sum(vec##SZ);                       \
    bool vec##SZ##_cmp(vec##SZ, vec##SZ);               \
    float vec##SZ##_length_sqr(vec##SZ);                \
    float vec##SZ##_length(vec##SZ);                    \
    float vec##SZ##_dot(vec##SZ, vec##SZ);              \
    vec##SZ vec##SZ##_normalize(vec##SZ);               \
    float vec##SZ##_distance_sqr(vec##SZ, vec##SZ);     \
    float vec##SZ##_distance(vec##SZ, vec##SZ);         \
    vec##SZ vec##SZ##_clamp(vec##SZ, vec##SZ, vec##SZ); \
    vec##SZ vec##SZ##_lerp(vec##SZ, vec##SZ, float);
__PAUL_MATH_TYPES
#undef X
typedef vec4 quat;

#ifndef PAUL_MATH_NO_MATRICES
#ifdef __cplusplus
template<typename T, int N> class mat {
protected:
    std::array<std::array<T, N>, N> data;
public:
    mat() {
        for (int i = 0; i < N; i++)
            data[i].fill(0);
    }
    mat(std::initializer_list<std::initializer_list<T>> init) {
        if (init.size() != N)
            throw std::invalid_argument("Initializer list size does not match matrix size");
        int i = 0;
        for (const auto &row : init) {
            if (row.size() != N)
                throw std::invalid_argument("Row size does not match matrix size");
            std::copy(row.begin(), row.end(), data[i++].begin());
        }
    }
    std::array<T, N> &operator[](int index) { return data[index]; }
    const std::array<T, N> &operator[](int index) const { return data[index]; }
    int size() const { return N; }
};

class mat2: public mat<float, 2> {
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    mat2() {}
    mat2(float a, float b, float c, float d) {
        data[0][0] = a; data[1][0] = b;
        data[0][1] = c; data[1][1] = d;
    }
};

class mat3: public mat<float, 3> {
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m02 = _Proxy<float>(&data[0][2]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    _Proxy<float> m12 = _Proxy<float>(&data[1][2]);
    _Proxy<float> m20 = _Proxy<float>(&data[2][0]);
    _Proxy<float> m21 = _Proxy<float>(&data[2][1]);
    _Proxy<float> m22 = _Proxy<float>(&data[2][2]);
    mat3() {}
    mat3(float a, float b, float c,
         float d, float e, float f,
         float g, float h, float i) {
        data[0][0] = a; data[1][0] = b; data[2][0] = c;
        data[0][1] = d; data[1][1] = e; data[2][1] = f;
        data[0][2] = g; data[1][2] = h; data[2][2] = i;
    }
};

class mat4: public mat<float, 4> {
public:
    _Proxy<float> m00 = _Proxy<float>(&data[0][0]);
    _Proxy<float> m01 = _Proxy<float>(&data[0][1]);
    _Proxy<float> m02 = _Proxy<float>(&data[0][2]);
    _Proxy<float> m03 = _Proxy<float>(&data[0][3]);
    _Proxy<float> m10 = _Proxy<float>(&data[1][0]);
    _Proxy<float> m11 = _Proxy<float>(&data[1][1]);
    _Proxy<float> m12 = _Proxy<float>(&data[1][2]);
    _Proxy<float> m13 = _Proxy<float>(&data[1][3]);
    _Proxy<float> m20 = _Proxy<float>(&data[2][0]);
    _Proxy<float> m21 = _Proxy<float>(&data[2][1]);
    _Proxy<float> m22 = _Proxy<float>(&data[2][2]);
    _Proxy<float> m23 = _Proxy<float>(&data[2][3]);
    _Proxy<float> m30 = _Proxy<float>(&data[3][0]);
    _Proxy<float> m31 = _Proxy<float>(&data[3][1]);
    _Proxy<float> m32 = _Proxy<float>(&data[3][2]);
    _Proxy<float> m33 = _Proxy<float>(&data[3][3]);
    mat4() {}
    mat4(float a, float b, float c, float d,
         float e, float f, float g, float h,
         float i, float j, float k, float l,
         float m, float n, float o, float p) {
        data[0][0] = a; data[1][0] = b; data[2][0] = c; data[3][0] = d;
        data[0][1] = e; data[1][1] = f; data[2][1] = g; data[3][1] = h;
        data[0][2] = i; data[1][2] = j; data[2][2] = k; data[3][2] = l;
        data[0][3] = m; data[1][3] = n; data[2][3] = o; data[3][3] = p;
    }
};
#else
#define matrix(X) __attribute__((matrix_type((X), (X))))
#define X(N) \
    typedef float mat##N##N matrix(N);
__PAUL_MATH_TYPES
#undef X
#endif // __cplusplus

#define X(N)                                      \
    typedef mat##N##N mat##N;                     \
    mat##N Mat##N(void);                          \
    mat##N mat##N##_identity(void);               \
    bool mat##N##_is_identity(mat##N mat);        \
    bool mat##N##_is_zero(mat##N mat);            \
    bool mat##N##_cmp(mat##N a, mat##N b);        \
    float mat##N##_trace(mat##N mat);             \
    mat##N mat##N##_transpose(mat##N);            \
    vec##N mat##N##_column(mat##N, unsigned int); \
    vec##N mat##N##_row(mat##N, unsigned int);
__PAUL_MATH_TYPES
#undef X
#endif

#ifndef PAUL_MATH_NO_PRINT
#ifdef __cplusplus
template<typename T> void bla_print(const T& data);
#define X(SZ) template<> void bla_print<vec##SZ>(const vec##SZ& data);
__PAUL_MATH_TYPES
#undef X
#ifndef PAUL_MATH_NO_MATRICES
#define X(SZ) template<> void bla_print<mat##SZ>(const mat##SZ& data);
__PAUL_MATH_TYPES
#undef X
#endif
#else
#define X(SZ) void vec##SZ##_print(vec##SZ);
__PAUL_MATH_TYPES
#undef X
#ifndef PAUL_MATH_NO_MATRICES
#define X(SZ) void mat##SZ##_print(mat##SZ);
__PAUL_MATH_TYPES
#undef X
#endif // PAUL_MATH_NO_MATRICES

#ifndef PAUL_NO_GENERICS
#ifndef PAUL_MATH_NO_MATRICES
#define bla_print(data) _Generic((data), \
    vec2: vec2_print,                    \
    vec3: vec3_print,                    \
    vec4: vec4_print,                    \
    mat2: mat2_print,                    \
    mat3: mat3_print,                    \
    mat4: mat4_print,                    \
    default: printf("Unsupported type\n"))(data)
#else
#define bla_print(data) _Generic((data), \
    vec2: vec2_print,                    \
    vec3: vec3_print,                    \
    vec4: vec4_print,                    \
    default: printf("Unsupported type\n"))(data)
#endif // PAUL_MATH_NO_MATRICES
#endif // PAUL_NO_GENERICS
#endif // PAUL_MATH_NO_PRINT
#endif

#ifndef COUNT_ARGS
#define COUNT_ARGS(...) _NARG_(__VA_ARGS__, _RSEQ())
#define _NARGS(...) _SEQ(__VA_ARGS__)
#define _SEQ(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,_125,_126,_127,N,...) N
#define _RSEQ() 127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#endif

#define ___Vec(NAME, N) NAME##N
#define __Vec(NAME, N) ___Vec(NAME, N)
#define _Vec(FUNC, ...) __Vec(FUNC, COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)
#define Vec(...) _Vec(Vec, __VA_ARGS__)
#ifdef __cplusplus
#define Vec2(x, y) vec2(x, y)
#define Vec3(x, y, z) vec3(x, y, z)
#define Vec4(x, y, z, w) vec4(x, y, z, w)
#define Quat(x, y, z, w) quat(x, y, z, w)
#else
#define Vec2(x, y) (vec2){x, y}
#define Vec3(x, y, z) (vec3){x, y, z}
#define Vec4(x, y, z, w) (vec4){x, y, z, w}
#define Quat(x, y, z, w) (quat){x, y, z, w}
#endif

#ifndef MAP
#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT
#define MAP_COMMA ,

#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
#define MAP_NEXT(test, next) MAP_NEXT1(MAP_GET_END test, next)

#define MAP0(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)

#define MAP_LIST_NEXT1(test, next) MAP_NEXT0(test, MAP_COMMA next, 0)
#define MAP_LIST_NEXT(test, next) MAP_LIST_NEXT1(MAP_GET_END test, next)

#define MAP_LIST0(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST1)(f, peek, __VA_ARGS__)
#define MAP_LIST1(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST0)(f, peek, __VA_ARGS__)

#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define MAP_LIST0_UD(f, userdata, x, peek, ...) f(x, userdata) MAP_LIST_NEXT(peek, MAP_LIST1_UD)(f, userdata, peek, __VA_ARGS__)
#define MAP_LIST1_UD(f, userdata, x, peek, ...) f(x, userdata) MAP_LIST_NEXT(peek, MAP_LIST0_UD)(f, userdata, peek, __VA_ARGS__)

#define MAP_LIST_UD(f, userdata, ...) EVAL(MAP_LIST1_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#endif

#define SWIZZLE_UD(V, VEC) VEC.V
#define swizzle(V, ...) {MAP_LIST_UD(SWIZZLE_UD, V, __VA_ARGS__)}

float vec2_angle(vec2 v1, vec2 v2);
vec2 vec2_rotate(vec2 v, float angle);
vec2 vec2_move_towards(vec2 v, vec2 target, float maxDistance);
vec2 vec2_reflect(vec2 v, vec2 normal);
float vec2_cross(vec2 a, vec2 b);

vec3 vec3_reflect(vec3 v, vec3 normal);
vec3 vec3_cross(vec3 v1, vec3 v2);
vec3 vec3_perpendicular(vec3 v);
float vec3_angle(vec3 v1, vec3 v2);
vec3 quat_rotate_vec3(vec3 v, quat q);
vec3 vec3_rotate_axis_angle(vec3 v, vec3 axis, float angle);
vec3 vec3_refract(vec3 v, vec3 n, float r);
vec3 vec3_barycenter(vec3 p, vec3 a, vec3 b, vec3 c);

quat quat_identity(void);
quat quat_mul(quat q1, quat q2);
quat quat_invert(quat q);
quat quat_to_from_vec3(vec3 from, vec3 to);
quat quat_from_axis_angle(vec3 axis, float angle);
void quat_to_axis_angle(quat q, vec3 *outAxis, float *outAngle);
quat quat_from_euler(float pitch, float yaw, float roll);
vec3 quat_to_euler(quat q);
int quat_cmp(quat p, quat q);

#ifndef PAUL_MATH_NO_MATRICES
vec3 vec3_transform(vec3 v, mat4 mat);
vec3 vec3_unproject(vec3 source, mat4 projection, mat4 view);
float mat4_determinant(mat4 mat);

quat quat_from_mat4(mat4 mat);
mat4 mat4_from_quat(quat q);
quat quat_transform(quat q, mat4 mat);

mat4 mat4_invert(mat4 mat);
mat4 mat4_translate(vec3 v);
mat4 mat4_rotate(vec3 axis, float angle);
mat4 mat4_scale(vec3 scale);
mat4 frustum(float left, float right, float bottom, float top, float near, float far);
mat4 perspective(float fovY, float aspect, float nearPlane, float farPlane);
mat4 ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
mat4 look_at(vec3 center, vec3 target, vec3 up);
#endif

enum easing_fn {
    EASE_LINEAR = 0,
    EASE_SINE,
    EASE_CIRCULAR,
    EASE_CUBIC,
    EASE_QUAD,
    EASE_EXPONENTIAL,
    EASE_BACK,
    EASE_BOUNCE,
    EASE_ELASTIC
};

enum easing_t {
    EASE_IN = 1,
    EASE_OUT,
    EASE_INOUT
};

float ease(enum easing_fn func, enum easing_t type, float t, float b, float c, float d);

#ifdef __cplusplus
}
#endif
#endif // PAUL_MATH_HEADER

#if defined(PAUL_MATH_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION)
#ifndef PAUL_MATH_FLOAT_CMP_EXACT
#define FLT_CMP(A, B) \
    (fabs((A) - (B)) <= PAUL_MATH_FLOAT_EPSILON * fmax(1.f, fmax(fabs(A), fabs(B))))
#else
#define FLT_CMP(A, B) \
    ((A) == (B))
#endif

#ifndef PAUL_MATH_NO_MATRICES
#define X(N)                                                \
    mat##N Mat##N(void)                                     \
    {                                                       \
        mat##N mat;                                         \
        memset(&mat, 0, sizeof(float) * (N * N));           \
        return mat;                                         \
    }                                                       \
    mat##N mat##N##_identity(void)                          \
    {                                                       \
        mat##N mat = Mat##N();                              \
        for (int i = 0; i < N; i++)                         \
            mat[i][i] = 1.f;                                \
        return mat;                                         \
    }                                                       \
    bool mat##N##_is_identity(mat##N mat)                   \
    {                                                       \
        for (int y = 0; y < N; y++)                         \
            for (int x = 0; x < N; x++)                     \
                if (mat[y][x] != (x == y ? 1.f : 0.f))      \
                    return false;                           \
        return true;                                        \
    }                                                       \
    bool mat##N##_is_zero(mat##N mat)                       \
    {                                                       \
        for (int y = 0; y < N; y++)                         \
            for (int x = 0; x < N; x++)                     \
                if (mat[y][x] != 0.f)                       \
                    return false;                           \
        return true;                                        \
    }                                                       \
    bool mat##N##_cmp(mat##N a, mat##N b)                   \
    {                                                       \
        for (int y = 0; y < N; y++)                         \
            for (int x = 0; x < N; x++)                     \
                if (!FLT_CMP(a[y][x], b[y][x]))             \
                    return false;                           \
        return true;                                        \
    }                                                       \
    float mat##N##_trace(mat##N mat)                        \
    {                                                       \
        float result = 0.f;                                 \
        for (int i = 0; i < N; i++)                         \
            result += mat[i][i];                            \
        return result;                                      \
    }                                                       \
    mat##N mat##N##_transpose(mat##N mat)                   \
    {                                                       \
        mat##N result = Mat##N();                           \
        for (int x = 0; x < N; x++)                         \
            for (int y = 0; y < N; y++)                     \
                result[x][y] = mat[y][x];                   \
        return result;                                      \
    }                                                       \
    vec##N mat##N##_column(mat##N mat, unsigned int column) \
    {                                                       \
        vec##N result = vec##N##_zero();                    \
        if (column >= N)                                    \
            return result;                                  \
        for (int i = 0; i < N; i++)                         \
            result[i] = mat[column][i];                     \
        return result;                                      \
    }                                                       \
    vec##N mat##N##_row(mat##N mat, unsigned int row)       \
    {                                                       \
        vec##N result = vec##N##_zero();                    \
        if (row >= N)                                       \
            return result;                                  \
        for (int i = 0; i < N; i++)                         \
            result[i] = mat[i][row];                        \
        return result;                                      \
    }
__PAUL_MATH_TYPES
#undef X
#endif // PAUL_MATH_NO_MATRICES

#define X(N)                                                  \
    vec##N vec##N##_zero(void)                                \
    {                                                         \
        return (vec##N){0};                                   \
    }                                                         \
    bool vec##N##_is_zero(vec##N vec)                         \
    {                                                         \
        for (int i = 0; i < N; i++)                           \
            if (vec[i] != 0.f)                                \
                return false;                                 \
                return true;                                  \
    }                                                         \
    float vec##N##_sum(vec##N vec)                            \
    {                                                         \
        float result = 0.f;                                   \
        for (int i = 0; i < N; i++)                           \
            result += vec[i];                                 \
        return result;                                        \
    }                                                         \
    bool vec##N##_cmp(vec##N a, vec##N b)                     \
    {                                                         \
        for (int i = 0; i < N; i++)                           \
            if (!FLT_CMP(a[i], b[i]))                         \
                return false;                                 \
        return true;                                          \
    }                                                         \
    float vec##N##_length_sqr(vec##N vec)                     \
    {                                                         \
        return vec##N##_sum(vec * vec);                       \
    }                                                         \
    float vec##N##_length(vec##N vec)                         \
    {                                                         \
        return sqrt(vec##N##_length_sqr(vec));                \
    }                                                         \
    float vec##N##_dot(vec##N a, vec##N b)                    \
    {                                                         \
        return vec##N##_sum(a * b);                           \
    }                                                         \
    vec##N vec##N##_normalize(vec##N vec)                     \
    {                                                         \
        vec##N result = vec##N##_zero();                      \
        float L = vec##N##_length(vec);                       \
        for (int i = 0; i < N; i++)                           \
            result[i] = vec[i] * (1.f / L);                   \
        return result;                                        \
    }                                                         \
    float vec##N##_distance_sqr(vec##N a, vec##N b)           \
    {                                                         \
        return vec##N##_length_sqr(b - a);                    \
    }                                                         \
    float vec##N##_distance(vec##N a, vec##N b)               \
    {                                                         \
        return sqrt(vec##N##_distance_sqr(a, b));             \
    }                                                         \
    vec##N vec##N##_clamp(vec##N vec, vec##N min, vec##N max) \
    {                                                         \
        vec##N result = vec##N##_zero();                      \
        for (int i = 0; i < N; i++)                           \
            result[i] = clamp(vec[i], min[i], max[i]);        \
        return result;                                        \
    }                                                         \
    vec##N vec##N##_lerp(vec##N a, vec##N b, float t)         \
    {                                                         \
        return a + t * (b - a);                               \
    }
__PAUL_MATH_TYPES
#undef X

#ifndef PAUL_MATH_NO_PRINT
#ifdef __cplusplus
#define X(SZ) template<> void bla_print<vec##SZ>(const vec##SZ& data) { vec##N##_print(data); }
__PAUL_MATH_TYPES
#undef X
#ifndef PAUL_MATH_NO_MATRICES
#define X(SZ) template<> void bla_print<mat##SZ>(const mat##SZ& data) { mat##SZ##_print(data); }
__PAUL_MATH_TYPES
#undef X
#endif
#else
#define X(N)                        \
    void vec##N##_print(vec##N vec) \
    {                               \
        printf("{ ");               \
        for (int i = 0; i < N; i++) \
            printf("%.6f ", vec[i]);  \
        puts("}");                  \
    }
__PAUL_MATH_TYPES
#undef X
#ifndef PAUL_MATH_NO_MATRICES
#define X(N)                                \
    void mat##N##_print(mat##N mat)         \
    {                                       \
        for (int x = 0; x < N; x++)         \
        {                                   \
            printf("| ");                   \
            for (int y = 0; y < N; y++)     \
                printf("%.6f ", mat[x][y]); \
            printf("|\n");                  \
        }                                   \
    }
__PAUL_MATH_TYPES
#undef X
#endif // PAUL_MATH_NO_MATRICES
#endif // __cplusplus
#endif // PAUL_MATH_NO_PRINT

float vec2_angle(vec2 v1, vec2 v2) {
    return atan2(v2.y, v2.x) - atan2(v1.y, v1.x);
}

vec2 vec2_rotate(vec2 v, float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return Vec2(v.x*c - v.y*s,  v.x*s + v.y*c);
}

vec2 vec2_move_towards(vec2 v, vec2 target, float maxDistance) {
    vec2 delta = target - v;
    float dist = vec2_length_sqr(delta);
    if (!dist || (maxDistance >= 0 && dist <= maxDistance * maxDistance))
        return target;
    else
        return v + (delta / (sqrt(dist) * maxDistance));
}

vec2 vec2_reflect(vec2 v, vec2 normal) {
    return v - (2.f * normal) * vec2_dot(v, normal);
}

float vec2_cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

vec3 vec3_reflect(vec3 v, vec3 normal) {
    return v - (2.f * normal) * vec3_dot(v, normal);
}

vec3 vec3_cross(vec3 v1, vec3 v2) {
    return Vec3(v1.y*v2.z - v1.z*v2.y,
                v1.z*v2.x - v1.x*v2.z,
                v1.x*v2.y - v1.y*v2.x);
}

vec3 vec3_perpendicular(vec3 v) {
    float min = (float) fabs(v.x);
    vec3 a = {1.f, 0.f, 0.f};
    if (fabs(v.y) < min) {
        min = (float) fabs(v.y);
        a = (vec3){0.f, 1.f, 0.f};
    }
    if (fabs(v.z) < min)
        a = vec3_zero();
    return Vec3(v.y * a.z - v.z * a.y,
                v.z * a.x - v.x * a.z,
                v.x * a.y - v.y * a.x);
}

float vec3_angle(vec3 v1, vec3 v2) {
    return atan2(vec3_length(vec3_cross(v1, v2)), vec3_dot(v1, v2));
}

vec3 quat_rotate_vec3(vec3 v, quat q) {
    return Vec3(v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) + v.y * (2 * q.x * q.y - 2 * q.w * q.z) + v.z * (2 * q.x * q.z + 2 * q.w * q.y),
                v.x * (2 * q.w * q.z + 2 * q.x * q.y) + v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) + v.z * (-2 * q.w * q.x + 2 * q.y * q.z),
                v.x * (-2 * q.w * q.y + 2 * q.x * q.z) + v.y * (2 * q.w * q.x + 2 * q.y * q.z) + v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
}

vec3 vec3_rotate_axis_angle(vec3 v, vec3 axis, float angle) {
    // Using Euler-Rodrigues Formula
    // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

    axis *= (1.f / (clamp(vec3_length(axis), 0.f, 1.f)));

    angle /= 2.f;
    vec3 w = axis * sin(angle);
    vec3 wv = vec3_cross(w, v);
    return v + (wv * (cos(angle) * 2.f)) + (vec3_cross(w, wv) * 2.f);
}

vec3 vec3_refract(vec3 v, vec3 n, float r) {
    float dot = vec3_dot(v, n);
    float d = 1.f - r*r*(1.f - dot*dot);
    return d < 0 ? vec3_zero() : r * v - (r * dot + sqrt(d)) * n;
}

vec3 vec3_barycenter(vec3 p, vec3 a, vec3 b, vec3 c) {
    vec3 v0 = b - a;
    vec3 v1 = c - a;
    vec3 v2 = p - a;
    float d00 = vec3_dot(v0, v1);
    float d01 = vec3_dot(v1, v1);
    float d11 = vec3_dot(v1, v1);
    float d20 = vec3_dot(v2, v0);
    float d21 = vec3_dot(v2, v1);
    float denom = d00*d11 - d01*d01;
    float y = (d11*d20 - d01*d21)/denom;
    float z = (d00*d21 - d01*d20)/denom;
    return Vec3(1.f - (z + y), y, z);
}

quat quat_zero(void) {
    return Quat(0.f, 0.f, 0.f, 0.f);
}

quat quat_identity(void) {
    return Quat(0.f, 0.f, 0.f, 1.f);
}

quat quat_mul(quat q1, quat q2) {
    float qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
    float qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;
    return Quat(qax * qbw + qaw * qbx + qay * qbz - qaz * qby,
                qay * qbw + qaw * qby + qaz * qbx - qax * qbz,
                qaz * qbw + qaw * qbz + qax * qby - qay * qbx,
                qaw * qbw - qax * qbx - qay * qby - qaz * qbz);
}

quat quat_invert(quat q) {
    float lsqr = vec4_length_sqr(q);
    quat result = q;
    if (lsqr != 0.f) {
        float inv = 1.f / lsqr;
        result *= Quat(-inv, -inv, -inv, inv);
    }
    return result;
}

quat quat_to_from_vec3(vec3 from, vec3 to) {
    vec3 cross = vec3_cross(from, to);
    return vec4_normalize(Quat(cross.x, cross.y, cross.z, 1.f + vec3_dot(from, to)));
}

#ifndef PAUL_MATH_NO_MATRICES
quat quat_from_mat4(mat4 mat) {
    float fourWSquaredMinus1 = mat[0][0] + mat[1][1] + mat[2][2];
    float fourXSquaredMinus1 = mat[0][0] - mat[1][1] - mat[2][2];
    float fourYSquaredMinus1 = mat[1][1] - mat[0][0] - mat[2][2];
    float fourZSquaredMinus1 = mat[2][2] - mat[0][0] - mat[1][1];

    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.f) * .5f;
    float mult = .25f / biggestVal;
    switch (biggestIndex) {
        case 0:
            return (quat) {
                (mat[2][1] - mat[1][2]) * mult,
                (mat[0][2] - mat[2][0]) * mult,
                (mat[1][0] - mat[0][1]) * mult,
                biggestVal
            };
            break;
        case 1: // X is biggest
            return (quat){
                biggestVal,
                (mat[2][1] - mat[1][2]) * mult,
                (mat[0][2] + mat[2][0]) * mult,
                (mat[1][0] + mat[0][1]) * mult
            };
        case 2: // Y is biggest
            return (quat){
                (mat[1][0] + mat[0][1]) * mult,
                biggestVal,
                (mat[2][1] - mat[1][2]) * mult,
                (mat[0][2] + mat[2][0]) * mult
            };
        case 3: // Z is biggest
            return (quat){
                (mat[0][2] + mat[2][0]) * mult,
                (mat[2][1] - mat[1][2]) * mult,
                biggestVal,
                (mat[1][0] + mat[0][1]) * mult
            };
        default:
            return quat_zero();
    }
}

#ifndef PAUL_MATH_NO_MATRICES
vec3 vec3_unproject(vec3 source, mat4 projection, mat4 view) {
    quat p = quat_transform(Quat(source.x, source.y, source.z, 1.f), mat4_invert(view * projection));
    return Vec3(p.x / p.w,
                p.y / p.w,
                p.z / p.w);
}

vec3 vec3_transform(vec3 v, mat4 mat) {
    return Vec3(mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3],
                mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3],
                mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3]);
}

mat4 mat4_from_quat(quat q) {
    float a2 = q.x*q.x;
    float b2 = q.y*q.y;
    float c2 = q.z*q.z;
    float ac = q.x*q.z;
    float ab = q.x*q.y;
    float bc = q.y*q.z;
    float ad = q.w*q.x;
    float bd = q.w*q.y;
    float cd = q.w*q.z;

    mat4 result = mat4_identity();
    result[0][0] = 1 - 2 * (b2 + c2);
    result[1][0] = 2 * (ab + cd);
    result[2][0] = 2 * (ac - bd);

    result[0][1] = 2 * (ab - cd);
    result[1][1] = 1 - 2 * (a2 + c2);
    result[2][1] = 2 * (bc + ad);

    result[0][2] = 2 * (ac + bd);
    result[1][2] = 2 * (bc - ad);
    result[2][2] = 1 - 2 * (a2 + b2);
    return result;
}

quat quat_from_axis_angle(vec3 axis, float angle) {
    float axisLength = vec3_length(axis);
    if (axisLength == 0.f)
        return quat_identity();

    axis = vec3_normalize(axis);
    angle *= .5f;
    float sinres = sin(angle);
    float cosres = cos(angle);
    return Quat(axis.x * sinres,
                axis.y * sinres,
                axis.z * sinres,
                cosres);
}
#endif // PAUL_MATH_NO_MATRICES

void quat_to_axis_angle(quat q, vec3 *outAxis, float *outAngle) {
    if (fabs(q.w) > 1.f)
        q = vec4_normalize(q);
    float resAngle = 2.f * acos(q.w);
    float den = sqrt(1.f - q.w * q.w);
    vec3 qxyz = Vec3(q.x, q.y, q.z);
    vec3 resAxis = den > PAUL_MATH_FLOAT_EPSILON ? qxyz / den : Vec3(1.f, 0.f, 0.f);
    *outAxis = resAxis;
    *outAngle = resAngle;
}

quat quat_from_euler(float pitch, float yaw, float roll) {
    float x0 = cos(pitch * .5f);
    float x1 = sin(pitch * .5f);
    float y0 = cos(yaw   * .5f);
    float y1 = sin(yaw   * .5f);
    float z0 = cos(roll  * .5f);
    float z1 = sin(roll  * .5f);
    return Quat(x1 * y0 * z0 - x0 * y1 * z1,
                x0 * y1 * z0 + x1 * y0 * z1,
                x0 * y0 * z1 - x1 * y1 * z0,
                x0 * y0 * z0 + x1 * y1 * z1);
}

vec3 quat_to_euler(quat q) {
    // Roll (x-axis rotation)
    float x0 = 2.f * (q.w * q.x + q.y * q.z);
    float x1 = 1.f - 2.f * (q.x * q.x + q.y * q.y);
    // Pitch (y-axis rotation)
    float y0 = 2.f * (q.w * q.y - q.z * q.x);
    y0 = y0 > 1.f ? 1.f : y0;
    y0 = y0 < -1.f ? -1.f : y0;
    // Yaw (z-axis rotation)
    float z0 = 2.f * (q.w * q.z + q.x * q.y);
    float z1 = 1.f - 2.f * (q.y * q.y + q.z * q.z);

    return Vec3(atan2(x0, x1),
                asin(y0),
                atan2(z0, z1));
}

quat quat_transform(quat q, mat4 mat) {
    return Quat(mat[0][0] * q.x + mat[0][1] * q.y + mat[0][2] * q.z + mat[0][3] * q.w,
                mat[1][0] * q.x + mat[1][1] * q.y + mat[1][2] * q.z + mat[1][3] * q.w,
                mat[2][0] * q.x + mat[2][1] * q.y + mat[2][2] * q.z + mat[2][3] * q.w,
                mat[3][0] * q.x + mat[3][1] * q.y + mat[3][2] * q.z + mat[3][3] * q.w);
}

int quat_cmp(quat p, quat q) {
    return FLT_CMP(p.x, q.x) && FLT_CMP(p.y, q.y) && FLT_CMP(p.z, q.z) && FLT_CMP(p.w, q.w);
}

float mat4_determinant(mat4 mat) {
    return mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0] - mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0] - mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0] + mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0] + mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0] - mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0] - mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1] + mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1] + mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1] - mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1] - mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1] + mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1] + mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2] - mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2] - mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2] + mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2] + mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2] - mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2] - mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3] + mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3] + mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3] - mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3] - mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3] + mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3];
}

mat4 mat4_invert(mat4 mat) {
    float b00 = mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
    float b01 = mat[0][0]*mat[2][1] - mat[2][0]*mat[0][1];
    float b02 = mat[0][0]*mat[3][1] - mat[3][0]*mat[0][1];
    float b03 = mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1];
    float b04 = mat[1][0]*mat[3][1] - mat[3][0]*mat[1][1];
    float b05 = mat[2][0]*mat[3][1] - mat[3][0]*mat[2][1];
    float b06 = mat[0][2]*mat[1][3] - mat[1][2]*mat[0][3];
    float b07 = mat[0][2]*mat[2][3] - mat[2][2]*mat[0][3];
    float b08 = mat[0][2]*mat[3][3] - mat[3][2]*mat[0][3];
    float b09 = mat[1][2]*mat[2][3] - mat[2][2]*mat[1][3];
    float b10 = mat[1][2]*mat[3][3] - mat[3][2]*mat[1][3];
    float b11 = mat[2][2]*mat[3][3] - mat[3][2]*mat[2][3];
    float invDet = 1.f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

    mat4 result = Mat4();
    result[0][0] = (mat[1][1]*b11 - mat[2][1]*b10 + mat[3][1]*b09)*invDet;
    result[1][0] = (-mat[1][0]*b11 + mat[2][0]*b10 - mat[3][0]*b09)*invDet;
    result[2][0] = (mat[1][3]*b05 - mat[2][3]*b04 + mat[3][3]*b03)*invDet;
    result[3][0] = (-mat[1][2]*b05 + mat[2][2]*b04 - mat[3][2]*b03)*invDet;
    result[0][1] = (-mat[0][1]*b11 + mat[2][1]*b08 - mat[3][1]*b07)*invDet;
    result[1][1] = (mat[0][0]*b11 - mat[2][0]*b08 + mat[3][0]*b07)*invDet;
    result[2][1] = (-mat[0][3]*b05 + mat[2][3]*b02 - mat[3][3]*b01)*invDet;
    result[3][1] = (mat[0][2]*b05 - mat[2][2]*b02 + mat[3][2]*b01)*invDet;
    result[0][2] = (mat[0][1]*b10 - mat[1][1]*b08 + mat[3][1]*b06)*invDet;
    result[1][2] = (-mat[0][0]*b10 + mat[1][0]*b08 - mat[3][0]*b06)*invDet;
    result[2][2] = (mat[0][3]*b04 - mat[1][3]*b02 + mat[3][3]*b00)*invDet;
    result[3][2] = (-mat[0][2]*b04 + mat[1][2]*b02 - mat[3][2]*b00)*invDet;
    result[0][3] = (-mat[0][1]*b09 + mat[1][1]*b07 - mat[2][1]*b06)*invDet;
    result[1][3] = (mat[0][0]*b09 - mat[1][0]*b07 + mat[2][0]*b06)*invDet;
    result[2][3] = (-mat[0][3]*b03 + mat[1][3]*b01 - mat[2][3]*b00)*invDet;
    result[3][3] = (mat[0][2]*b03 - mat[1][2]*b01 + mat[2][2]*b00)*invDet;
    return result;
}

mat4 mat4_translate(vec3 v) {
    mat4 result = mat4_identity();
    result[0][3] = v.x;
    result[1][3] = v.y;
    result[2][3] = v.z;
    return result;
}

mat4 mat4_rotate(vec3 axis, float angle) {
    vec3 a = vec3_normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float t = 1.f - c;

    mat4 result = mat4_identity();
    result[0][0] = a.x * a.x * t + c;
    result[1][0] = a.y * a.x * t + a.z * s;
    result[2][0] = a.z * a.x * t - a.y * s;
    result[0][1] = a.x * a.y * t - a.z * s;
    result[1][1] = a.y * a.y * t + c;
    result[2][1] = a.z * a.y * t + a.x * s;
    result[0][2] = a.x * a.z * t + a.y * s;
    result[1][2] = a.y * a.z * t - a.x * s;
    result[2][2] = a.z * a.z * t + c;
    return result;
}

mat4 mat4_scale(vec3 scale) {
    mat4 result = Mat4();
    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;
    result[3][3] = 1.f;
    return result;
}

mat4 frustum(float left, float right, float bottom, float top, float near, float far) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    mat4 result = Mat4();
    result[0][0] = (near * 2.f)/rl;
    result[1][1] = (near * 2.f)/tb;
    result[0][2] = (right + left)/rl;
    result[1][2] = (top + bottom)/tb;
    result[2][2] = -(far + near)/fn;
    result[3][2] = -1.f;
    result[2][3] = -(far * near * 2.f)/fn;
    return result;
}

mat4 perspective(float fovY, float aspect, float nearPlane, float farPlane) {
    float top = nearPlane * tan(fovY * 0.5f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    float rl = right - left;
    float tb = top - bottom;
    float fn = farPlane - nearPlane;

    mat4 result = Mat4();
    result[0][0] = (nearPlane * 2.0f) / rl;
    result[1][1] = (nearPlane * 2.0f) / tb;
    result[2][2] = -(farPlane + nearPlane) / fn;
    result[3][2] = -1.0f;
    result[2][3] = -(farPlane * nearPlane * 2.0f) / fn;
    result[3][3] = 0.0f;  // Explicit for clarity

    return result;
}

mat4 ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = farPlane - nearPlane;

    mat4 result = Mat4();
    result[0][0] = 2.0f / rl;
    result[1][1] = 2.0f / tb;
    result[2][2] = -2.0f / fn;
    result[0][3] = -(right + left) / rl;
    result[1][3] = -(top + bottom) / tb;
    result[2][3] = -(farPlane + nearPlane) / fn;
    result[3][3] = 1.0f;
    return result;
}

mat4 look_at(vec3 eye, vec3 target, vec3 up) {
    vec3 vz = vec3_normalize(eye - target);
    vec3 vx = vec3_normalize(vec3_cross(up, vz));
    vec3 vy = vec3_cross(vz, vx);

    mat4 result = Mat4();
    result[0][0] = vx.x;
    result[1][0] = vy.x;
    result[2][0] = vz.x;
    result[0][1] = vx.y;
    result[1][1] = vy.y;
    result[2][1] = vz.y;
    result[0][2] = vx.z;
    result[1][2] = vy.z;
    result[2][2] = vz.z;
    result[0][3] = -vec3_dot(vx, eye);
    result[1][3] = -vec3_dot(vy, eye);
    result[2][3] = -vec3_dot(vz, eye);
    result[3][3] = 1.f;
    return result;
}
#endif

static float ease_linear_None(float t, float b, float c, float d) {
    return (c * t / d + b);
}

static float ease_linear_in(float t, float b, float c, float d) {
    return (c * t / d + b);
}

static float ease_linear_out(float t, float b, float c, float d) {
    return (c * t / d + b);
}

static float ease_linear_inout(float t, float b, float c, float d) {
    return (c * t / d + b);
}

static float ease_sine_in(float t, float b, float c, float d) {
    return (-c * cos(t / d * (M_PI / 2.f)) + c + b);
}

static float ease_sine_out(float t, float b, float c, float d) {
    return (c * sin(t / d * (M_PI / 2.f)) + b);
}

static float ease_sine_inout(float t, float b, float c, float d) {
    return (-c / 2.f * (cos(M_PI * t / d) - 1.f) + b);
}

static float ease_circ_in(float t, float b, float c, float d) {
    t /= d;
    return (-c * (sqrt(1.f - t * t) - 1.f) + b);
}

static float ease_circ_out(float t, float b, float c, float d) {
    t = t / d - 1.f;
    return (c * sqrt(1.f - t * t) + b);
}

static float ease_circ_inout(float t, float b, float c, float d) {
    if ((t /= d / 2.f) < 1.f)
        return (-c / 2.f * (sqrt(1.f - t * t) - 1.f) + b);
    t -= 2.f;
    return (c / 2.f * (sqrt(1.f - t * t) + 1.f) + b);
}

static float ease_cubic_in(float t, float b, float c, float d) {
    t /= d;
    return (c * t * t * t + b);
}

static float ease_cubic_out(float t, float b, float c, float d) {
    t = t / d - 1.f;
    return (c * (t * t * t + 1.f) + b);
}

static float ease_cubic_inout(float t, float b, float c, float d) {
    if ((t /= d / 2.f) < 1.f)
        return (c / 2.f * t * t * t + b);
    t -= 2.f;
    return (c / 2.f * (t * t * t + 2.f) + b);
}

static float ease_quad_in(float t, float b, float c, float d) {
    t /= d;
    return (c * t * t + b);
}

static float ease_quad_out(float t, float b, float c, float d) {
    t /= d;
    return (-c * t * (t - 2.f) + b);
}

static float ease_quad_inout(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1)
        return (((c / 2) * (t * t)) + b);
    return (-c / 2.f * (((t - 1.f) * (t - 3.f)) - 1.f) + b);
}

static float ease_expo_in(float t, float b, float c, float d) {
    return (t == 0.f) ? b : (c * pow(2.f, 10.f * (t / d - 1.f)) + b);
}

static float ease_expo_out(float t, float b, float c, float d) {
    return (t == d) ? (b + c) : (c * (-pow(2.f, -10.f * t / d) + 1.f) + b);
}

static float ease_expo_inout(float t, float b, float c, float d) {
    if (t == 0.f)
        return b;
    if (t == d)
        return (b + c);
    if ((t /= d / 2.f) < 1.f)
        return (c / 2.f * pow(2.f, 10.f * (t - 1.f)) + b);

    return (c / 2.f * (-pow(2.f, -10.f * (t - 1.f)) + 2.f) + b);
}

static float ease_back_in(float t, float b, float c, float d) {
    float s = 1.70158f;
    float postFix = t /= d;
    return (c * (postFix) * t * ((s + 1.f) * t - s) + b);
}

static float ease_back_out(float t, float b, float c, float d) {
    float s = 1.70158f;
    t = t / d - 1.f;
    return (c * (t * t * ((s + 1.f) * t + s) + 1.f) + b);
}

static float ease_back_inout(float t, float b, float c, float d) {
    float s = 1.70158f;
    if ((t /= d / 2.f) < 1.f) {
        s *= 1.525f;
        return (c / 2.f * (t * t * ((s + 1.f) * t - s)) + b);
    }

    float postFix = t -= 2.f;
    s *= 1.525f;
    return (c / 2.f * ((postFix)*t * ((s + 1.f) * t + s) + 2.f) + b);
}

static float ease_bounce_out(float t, float b, float c, float d) {
    if ((t /= d) < (1.f / 2.75f)) {
        return (c * (7.5625f * t * t) + b);
    } else if (t < (2.f / 2.75f)) {
        float postFix = t -= (1.5f / 2.75f);
        return (c * (7.5625f * (postFix)*t + .75f) + b);
    } else if (t < (2.5 / 2.75)) {
        float postFix = t -= (2.25f / 2.75f);
        return (c * (7.5625f * (postFix)*t + .9375f) + b);
    } else {
        float postFix = t -= (2.625f / 2.75f);
        return (c * (7.5625f * (postFix)*t + .984375f) + b);
    }
}

static float ease_bounce_in(float t, float b, float c, float d) {
    return (c - ease_bounce_out(d - t, 0.f, c, d) + b);

}

static float ease_bounce_inout(float t, float b, float c, float d) {
    if (t < d / 2.f)
        return (ease_bounce_in(t * 2.f, 0.f, c, d) * .5f + b);
    else
        return (ease_bounce_out(t * 2.f - d, 0.f, c, d) * .5f + c * .5f + b);
}

static float ease_elastic_in(float t, float b, float c, float d) {
    if (t == 0.f)
        return b;
    if ((t /= d) == 1.f)
        return (b + c);

    float p = d * .3f;
    float a = c;
    float s = p / 4.f;
    float postFix = a * pow(2.f, 10.f * (t -= 1.f));

    return (-(postFix * sin((t * d - s) * (2.f * M_PI) / p)) + b);
}

static float ease_elastic_out(float t, float b, float c, float d) {
    if (t == 0.f)
        return b;
    if ((t /= d) == 1.f)
        return (b + c);

    float p = d * 0.3f;
    float a = c;
    float s = p / 4.f;

    return (a * pow(2.f, -10.f * t) * sin((t * d - s) * (2.f * M_PI) / p) + c + b);
}

static float ease_elastic_inout(float t, float b, float c, float d) {
    if (t == 0.f)
        return b;
    if ((t /= d / 2.f) == 2.f)
        return (b + c);

    float p = d * (0.3f * 1.5f);
    float a = c;
    float s = p / 4.f;

    if (t < 1.f) {
        float postFix = a * pow(2.f, 10.f * (t -= 1.f));
        return -.5f * (postFix * sin((t * d - s) * (2.f * M_PI) / p)) + b;
    }

    float postFix = a * pow(2.f, -10.f * (t -= 1.f));

    return (postFix * sin((t * d - s) * (2.f * M_PI) / p) * .5f + c + b);
}

float ease(enum easing_fn fn, enum easing_t type, float t, float b, float c, float d) {
    switch (fn) {
        default:
        case EASE_LINEAR:
            switch ((int)type) {
                default:
                case 0:
                    return ease_linear_None(t, b, c, d);
                case EASE_IN:
                    return ease_linear_in(t, b, c, d);
                case EASE_OUT:
                    return ease_linear_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_linear_inout(t, b, c, d);
            }
        case EASE_SINE:
            switch (type) {
                case EASE_IN:
                    return ease_sine_in(t, b, c, d);
                case EASE_OUT:
                    return ease_sine_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_sine_inout(t, b, c, d);
            };
        case EASE_CIRCULAR:
            switch (type) {
                case EASE_IN:
                    return ease_circ_in(t, b, c, d);
                case EASE_OUT:
                    return ease_circ_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_circ_inout(t, b, c, d);
            };
        case EASE_CUBIC:
            switch (type) {
                case EASE_IN:
                    return ease_cubic_in(t, b, c, d);
                case EASE_OUT:
                    return ease_cubic_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_cubic_inout(t, b, c, d);
            };
        case EASE_QUAD:
            switch (type) {
                case EASE_IN:
                    return ease_quad_in(t, b, c, d);
                case EASE_OUT:
                    return ease_quad_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_quad_inout(t, b, c, d);
            };
        case EASE_EXPONENTIAL:
            switch (type) {
                case EASE_IN:
                    return ease_expo_in(t, b, c, d);
                case EASE_OUT:
                    return ease_expo_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_expo_inout(t, b, c, d);
            };
        case EASE_BACK:
            switch (type) {
                case EASE_IN:
                    return ease_back_in(t, b, c, d);
                case EASE_OUT:
                    return ease_back_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_back_inout(t, b, c, d);
            };
        case EASE_BOUNCE:
            switch (type) {
                case EASE_IN:
                    return ease_bounce_in(t, b, c, d);
                case EASE_OUT:
                    return ease_bounce_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_bounce_inout(t, b, c, d);
            };
        case EASE_ELASTIC:
            switch (type) {
                case EASE_IN:
                    return ease_elastic_in(t, b, c, d);
                case EASE_OUT:
                    return ease_elastic_out(t, b, c, d);
                case EASE_INOUT:
                    return ease_elastic_inout(t, b, c, d);
            };
    }
}
#endif // PAUL_MATH_IMPLEMENTATION
