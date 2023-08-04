#pragma once

#include <stdint.h>
template <typename T>
struct Color{
    T r;
    T g;
    T b;
    T a;
    Color():r(0),g(0),b(0),a(0){};
    Color(T r,T g,T b,T a = 1):
        r(r),g(g),b(b),a(a){};
    Color(const Color & x)
        :r(x.r),g(x.g),b(x.b),a(x.a){}

    Color& operator+(const Color& u)
    {
        r += u.r;
        g += u.g;
        b += u.b;
        a += u.a;
        return *this;
    }
    Color& operator/(const float& u){
        r /= u;
        g /= u;
        b /= u;
        a /= u;
        return *this;
    }   
    Color & operator*(const float & u)
    {
        r *= u;
        g *= u;
        b *= u;
        a *= u;
        return *this;
    }
    Color & operator*(const Color & u)
    {
        r *= u.r;
        g *= u.g;
        b *= u.b;
        a *= u.a;
        return *this;
    }
};

