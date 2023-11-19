#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


#define vec2f vec2<float>
#define vec2i vec2<int>


template <typename T>
struct vec2 {
public:
    T x, y;

    vec2(float value)        : x(value), y(value) {}
    vec2(float _x, float _y) : x(_x)   , y(_y)    {}
    vec2()                   : x(0)    , y(0)     {}

    vec2 operator +  (vec2 const& other) { return vec2(x + other.x , y + other.y) ; }
    vec2 operator -  (vec2 const& other) { return vec2(x - other.x , y - other.y) ; }
    vec2 operator *  (vec2 const& other) { return vec2(x * other.x , y * other.y) ; }
    vec2 operator /  (vec2 const& other) { return vec2(x / other.x , y / other.y) ; }
    vec2 operator += (vec2 const& other) { return vec2(x += other.x, y += other.y); }
    vec2 operator -= (vec2 const& other) { return vec2(x -= other.x, y -= other.y); }
    vec2 operator *= (vec2 const& other) { return vec2(x *= other.x, y *= other.y); }
    vec2 operator /= (vec2 const& other) { return vec2(x /= other.x, y /= other.y); }
   
    float SquaredLength() const { return x * x + y * y        ; }
    float Length       () const { return sqrt(SquaredLength()); }

    vec2 Normalize() const { 
        if (Length() < 0.000001) { return this; }
        return this / Length();
    }

    vec2 Rotate(float angle) {
        return vec2(
            x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle)
        );
    }

    vec2 yx() { return vec2<T>(y, x); }

    sf::Vector2f ToSFML() { return sf::Vector2f(x, y); }

    friend std::ostream& operator<<(std::ostream& out, const vec2& value) {
        out << "vec2(" << value.x << ", " << value.y << ")";
        return out;
    }
};
