#include "../Common/color.h"
#include <stdint.h>
#include "../Common/vec.h"
#include <cmath>
struct Material{
    Color<float> ambient;
    Color<float> diffuse;
    Color<float> specular;

    // Diffuse + Specular
    Color<float> evaulate(vec3<float> normal,vec3<float> light_pos,vec3<float> eye)
    {
        const float PI = 3.1415926;
        // Diffuse
        Color<float> d = diffuse / PI;

        // Specular 
        vec3<float> h = normalize(light_pos + eye);
        int p = 100; // decay
        Color<float> s = specular * pow(fmax(0,dot(normal ,h)),p);
        return d+s;
    }
};