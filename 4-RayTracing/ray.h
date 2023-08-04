#pragma once
#include "../Common/vec.h"
class Ray{
public:
    Ray(vec3<float> o,vec3<float> d)
        : origin(o),direction(d){};


    vec3<float> origin;
    vec3<float> direction;   
};