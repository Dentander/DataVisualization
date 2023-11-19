#pragma once
#include "vec2.h"
#include <SFML/Graphics.hpp>
#include <cmath>


#define vec3f vec3<float>
#define vec3i vec3<int>


template <typename T>
struct vec3 {
public:
    T x, y, z;

    explicit vec3(float _value)        : x(_value), y(_value), z(_value) {}
    vec3(float _x, vec2<T> const& v)   : x(_x)    , y(v.x)   , z(v.y)    {}
    vec3(float _x, float _y, float _z) : x(_x)    , y(_y)    , z(_z)     {}
    vec3()                             : x(0)     , y(0)     , z(0)      {}

    vec3 operator + (vec3 const& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
    vec3 operator - (vec3 const& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
    vec3 operator * (vec3 const& other) const { return vec3(x * other.x, y * other.y, z * other.z); }
    vec3 operator / (vec3 const& other) const { return vec3(x / other.x, y / other.y, z / other.z); }
    vec3 operator * (float value)       const { return vec3(x * value  , y * value  , z * value)  ; }
    vec3 operator / (float value)       const { return vec3(x * value  , y * value  , z / value)  ; }
    vec3 operator - ()                  const { return vec3(-x         , -y         , -z)         ; }

    float SquaredLength() const { return x * x + y * y + z * z   ; }
    float Length()        const { return sqrt(SquaredLength())   ; }

    vec3 Normalize() { 
        if (Length() < 0.000001) { return this; }
        return this / Length();
    }

    vec3 Rotate(float horizontalAngle, float verticalAngle) {
        vec2f tmp = vec2f(x, z).Rotate(horizontalAngle);
        T tmpY = x * std::sin(verticalAngle);
        return vec3(tmp.x * std::cos(verticalAngle), tmpY, tmp.y);
    }
    
    vec2<T> xy()  { return vec2<T>(x, y); }
    vec2<T> yx()  { return vec2<T>(y, x); }
    vec2<T> xz()  { return vec2<T>(x, z); }
    vec2<T> zx()  { return vec2<T>(z, x); }
    vec2<T> yz()  { return vec2<T>(y, z); }
    vec2<T> zy()  { return vec2<T>(z, y); }
    vec3    xyz() { return vec3(x, y, z); }
    vec3    xzy() { return vec3(x, z, y); }
    vec3    yxz() { return vec3(y, x, z); }
    vec3    yzx() { return vec3(y, z, x); }
    vec3    zxy() { return vec3(z, x, y); }
    vec3    zyx() { return vec3(z, y, x); }

    sf::Vector3f ToSFML() const { return sf::Vector3f(x, y, z); }

    friend std::ostream& operator<<(std::ostream& out, const vec3& value) {
        out << "vec3(" << value.x << ", " << value.y << ", " << value.z << ")";
        return out;
    }
};

