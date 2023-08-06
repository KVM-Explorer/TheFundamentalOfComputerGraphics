#pragma once
#include "ray.h"
#include "surface.h"
#include <cmath>
#include <format>
#include <iostream>
#include <stdint.h>

class Light {
  public:
    virtual Color<float> illuminate(Ray r, HitRecord info) const = 0;
};

class PointLight : public Light {
public:
    vec3<float> position;
    Color<float> I;

  
    PointLight(vec3<float> p, Color<float> i) : position(p), I(i){};
    Color<float> illuminate(Ray r, HitRecord info) const{
        vec3<float> p = r.origin + r.direction * info.t; // hit point;
        vec3<float> pl = position - p; // hit point to light source
        float pl_len = len(pl);
        pl = normalize(pl); 
        vec3<float> n = info.normal;
        Color<float> E = I * fmax(0.0F, dot(n, pl)) /
                         (pl_len * pl_len); // Intensity decay with distance
        E = I * fmax(0.0F, dot(n, pl)); // line 26 中实测发现衰减的太快了，导致光线太暗，所以这里不衰减
        Color<float> k = info.material.evaluate(n, pl, r.origin);  
        return k * E;
    }
};

class DirectionLight : public Light {
    vec3<float> direction;
    Color<float> I;

  public:
    DirectionLight(vec3<float> d, Color<float> i) : direction(d), I(i) {}
    Color<float> illuminate(Ray r, HitRecord info) const {
        // vec3<float> p = r.origin + r.direction * info.t; // hit point;
        // vec3<float> pl = position - p; // hit point to light source
        // float pl_len = len(pl);
        // pl = normalize(pl) ;  //
        // vec3<float> n = info.normal;
        // Color<float> E = fmax(0,dot(n,pl)) * I / (pl_len*pl_len);
        // Color<float>  k = info.material.evaluate(n,position,r.origin);
        // TODO Direction Color
        return I * info.material.evaluate({}, {}, {});
    }
};

class AmbientLight : public Light {
    Color<float> I;

  public:
    AmbientLight(Color<float> i) : I(i) {}

    Color<float> illuminate(Ray r, HitRecord info) const {
        return info.material.ambient * I;
    }
};