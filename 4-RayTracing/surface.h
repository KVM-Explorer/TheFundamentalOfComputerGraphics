#pragma once
#include "../Common/vec.h"
#include "ray.h"
#include "material.h"

struct HitRecord{
    Material material;
    float t;
    vec3<float> normal;
       
};;

struct Surface{
    Surface(Material material):material(material){};
    virtual HitRecord hit(Ray ray,float t0,float t1) = 0;

    Material material;
};

