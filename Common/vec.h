#pragma once
template<typename  T>
struct vec3{
    T x;
    T y;
    T z;
    vec3() = default;
    vec3(T x,T y,T z):x(x),y(y),z(z){};
    vec3(const vec3<T> &v):x(v.x),y(v.y),z(v.z){};


    vec3 &operator-(const vec3 &u) {
        vec3 ret;
        ret.x = x -  u.x;
        ret.y = y -  u.y;
        ret.z = z -  u.z;
        return ret;
    }
    vec3 & operator*(const float & u)
    {
        vec3 ret;
        ret.x = x * u;
        ret.y = y * u;
        ret.z = z * u;
        return ret;
    }
    vec3 &operator+(const vec3 &u) {
        vec3 ret;
        ret.x = x + u.x;
        ret.y = y + u.y;
        ret.z = z + u.z;
        return ret;
    }
};

template<typename T>
T dot(const vec3<T>& a,const vec3<T>& b) {
    return a.x*b.x + a.y *b.y +a.z*b.z;
}

template<typename T>
float len(const vec3<T> & a)
{
    return sqrt(a.x*a.x +a.y*a.y +a.z*a.z);
}

template<typename T>
vec3<T> normalize(const vec3<T>& a)
{
    float l = len(a);
    return {a.x/l,a.y/l,a.z/l};
}