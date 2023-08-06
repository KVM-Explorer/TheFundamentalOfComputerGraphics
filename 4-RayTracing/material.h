#pragma once
#include "../Common/color.h"
#include <cstdint>
#include "../Common/vec.h"
#include "../Common/math_tools.h"
#include <cmath>
struct Material{
    Color<float> ambient;
    Color<float> diffuse;
    Color<float> specular;

    // Diffuse + Specular
    Color<float> evaluate(vec3<float> normal,vec3<float> light_pos,vec3<float> eye)
    {
        // Diffuse
        Color<float> d = diffuse * fmax(0,dot(normal,light_pos));

        // Specular
        vec3<float> h = normalize(light_pos + eye); 
        int p = 10; // decay
        Color<float> s = specular * pow(fmax(0,dot(normal ,h)),p);
        return d+s;
    }
};