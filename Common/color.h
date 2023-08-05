#pragma once

#include <stdint.h>
template <typename T> struct Color {
    T r;
    T g;
    T b;
    T a;
    Color() : r(0), g(0), b(0), a(1){};
    Color(T r, T g, T b, T a = 1) : r(r), g(g), b(b), a(a){};
    Color(const Color &x) : r(x.r), g(x.g), b(x.b), a(x.a) {}
    Color& operator=(const Color& x){
        r = x.r;
        g = x.g;
        b = x.b;
        a = x.a;
        return *this;}

    Color<T> operator+(const Color &u) const{
        Color<T> ret;
        ret.r = r + u.r;
        ret.g = g + u.g;
        ret.b = b + u.b;
        ret.a = a + u.a;
        return ret;
    }
    Color<T> operator/(const float &u) const{
        Color<T> ret;
        ret.r = r / u;
        ret.g = g / u;
        ret.b = b / u;
        ret.a = a / u;
        return ret;
    }
    Color<T> operator*(const float &u) const{
        Color<T> ret;
        ret.r = r * u;
        ret.g = g * u;
        ret.b = b * u;
        ret.a = a * u;
        return ret;
    }
    Color<T> operator*(const Color &u) const{
        Color<T> ret;
        ret.r = r * u.r;
        ret.g = g * u.g;
        ret.b = b * u.b;
        ret.a = a * u.a;
        return ret;
    }
};
