#pragma once 
#include "surface.h"
#include <cmath>

class Object{
    virtual HitRecord hit(Ray r,float t0,float t1) = 0;

};

class Sphere : public Object,public Surface{
public:
    Sphere(vec3<float> c,float r,Material m):Surface(m),center(c),radius(r){};
    HitRecord hit(Ray r,float t0,float t1);
      
    vec3<float> center;
    float radius;
};

inline HitRecord Sphere::hit(Ray r,float t0,float t1)
{ 
    float b = 2*dot(r.direction,r.origin - center);
    float a = dot(r.direction,r.direction); 
    float c = dot(r.origin - center,r.origin - center) - radius *radius;
    float delta = b*b - 4*a*c ;
    if (delta <= 0 ) return {0,{}};

    float x0 = (-2*dot(r.direction,r.origin - center) - sqrt(delta))/(2*dot(r.direction,r.direction));
    vec3<float> p0 = r.origin +r.direction *x0;
    vec3<float> normal0 = normalize(p0 - center);
    if(t0 <= x0 && x0 <=t1) return {x0,normal0};

    float x1 = (-2*dot(r.direction,r.origin - center) + sqrt(delta))/(2*dot(r.direction,r.direction));
    vec3<float> p1 = r.origin + r.direction*x1;
    vec3<float> normal1 = normalize(p1-center);
    if(t0 <= x1 && x1 <=t1) return {x1,normal1};
    return {0,{}};
}