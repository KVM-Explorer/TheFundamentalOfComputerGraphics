#pragma once 
#include "surface.h"
#include <cmath>
#include <iostream>
#include <format>
class Object {
public:
    virtual HitRecord hit(Ray r,float t0,float t1) = 0;

};

class Sphere : public Object,public Surface{
public:
    Sphere(vec3<float> c,float r,Material m):Surface(m),center(c),radius(r){};
    HitRecord hit(Ray r,float t0,float t1);
      
    vec3<float> center;
    float radius;
};

class Triangle : public Object, public Surface {
  public:
    Triangle(vec3<float> v0, vec3<float> v1, vec3<float> v2, Material m)
        : Surface(m), v0(v0), v1(v1), v2(v2) {
        normal = normalize(cross(v1 - v0, v2 - v0)); 
    };
    HitRecord hit(Ray r, float t0, float t1);

    vec3<float> v0, v1, v2;
    vec3<float> normal;
};

inline HitRecord Sphere::hit(Ray r,float t0,float t1)
{ 
    float b = 2*dot(r.direction,r.origin - center);
    float a = dot(r.direction,r.direction); 
    float c = dot(r.origin - center,r.origin - center) - radius *radius;
    float delta = b*b - 4*a*c ; 
    if (delta <= 0 ) return {material,INFINITY,{}};

    float x0 = (-2*dot(r.direction,r.origin - center) - sqrt(delta))/(2*dot(r.direction,r.direction));
    vec3<float> p0 = r.origin +r.direction *x0;
    vec3<float> normal0 = normalize(p0 - center);
    if(t0 <= x0 && x0 <=t1) return {material,x0,normal0};

    float x1 = (-2*dot(r.direction,r.origin - center) + sqrt(delta))/(2*dot(r.direction,r.direction));
    vec3<float> p1 = r.origin + r.direction*x1;
    vec3<float> normal1 = normalize(p1-center);
    if(t0 <= x1 && x1 <=t1) return {material,x1,normal1};
    return {material,INFINITY,{}};
}

inline HitRecord Triangle::hit(Ray r, float t0, float t1) {
    // vec3<float> e1 = v1 - v0;
    // vec3<float> e2 = v2 - v0;
    // vec3<float> s = r.origin - v0;
    // vec3<float> s1 = cross(r.direction, e2);
    // vec3<float> s2 = cross(s, e1);
    // float w = dot(s2, e2) / dot(s1, e1);
    // float u = dot(s1, s) / dot(s1, e1);
    // float v = dot(s2, r.direction) / dot(s1, e1);
    // if (t >= t0 && t <= t1 && u >= 0 && v >= 0 && u + v <= 1) {
    //     return {material, t, normal};
    // }
    // return {material, INFINITY, {}};

    // Cramer's rule

    float detM = (v0.x - v1.x) * (v0.y - v2.y) * r.direction.z +
                 (v0.y - v1.y) * (v0.z - v2.z) * r.direction.x +
                 (v0.z - v1.z) * (v0.x - v2.x) * r.direction.y -
                 (v0.z - v1.z) * (v0.y - v2.y) * r.direction.x -
                 (v0.y - v1.y) * (v0.x - v2.x) * r.direction.z -
                 (v0.x - v1.x) * (v0.z - v2.z) * r.direction.y;

    float detA = (v0.x - v2.x) * (v0.z - r.origin.z) * r.direction.y +
                 (v0.y - v2.y) * (v0.x - r.origin.x) * r.direction.z +
                 (v0.z - v2.z) * (v0.y - r.origin.y) * r.direction.x -
                 (v0.z - v2.z) * (v0.x - r.origin.x) * r.direction.y -
                 (v0.y - v2.y) * (v0.z - r.origin.z) * r.direction.x -
                 (v0.x - v2.x) * (v0.y - r.origin.y) * r.direction.z;

    float detB = (v0.x - v1.x) * (v0.y - r.origin.y) * r.direction.z +
                 (v0.y - v1.y) * (v0.z - r.origin.z) * r.direction.x +
                 (v0.z - v1.z) * (v0.x - r.origin.x) * r.direction.y -
                 (v0.z - v1.z) * (v0.y - r.origin.y) * r.direction.x -
                 (v0.y - v1.y) * (v0.x - r.origin.x) * r.direction.z -
                 (v0.x - v1.x) * (v0.z - r.origin.z) * r.direction.y;

    float detC = (v0.x - v1.x) * (v0.y - v2.y) * (v0.z - r.origin.z) +
                 (v0.y - v1.y) * (v0.z - v2.z) * (v0.x - r.origin.x) +
                 (v0.z - v1.z) * (v0.x - v2.x) * (v0.y - r.origin.y) -
                 (v0.z - v1.z) * (v0.y - v2.y) * (v0.x - r.origin.x) -
                 (v0.y - v1.y) * (v0.x - v2.x) * (v0.z - r.origin.z) -
                 (v0.x - v1.x) * (v0.z - v2.z) * (v0.y - r.origin.y);

    float alpha = detA / detM;
    float beta = detB / detM;
    float t = detC / detM;
    
    if (t >= t0 && t <= t1 && alpha >= 0 && beta >= 0 && alpha + beta <= 1) {
        return {material, t, normal};
    }
    return {material, INFINITY, {}};
}