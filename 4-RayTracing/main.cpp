#include "../Common/common.h"
#include "geometry.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

const int Width = 1024;
const int Height = 768;
const float Focal = 0.005;
const float L = -3.45 * 1e-6 * Width / 2;
const float R = 3.45 * 1e-6 * Width / 2;
const float T = 3.45 * 1e-6 * Height / 2;
const float B = -3.45 * 1e-6 * Height / 2;
const Color<float> DefaultColor = {0.411, 0.411, 0.411};
const float TriangleSize = 100;
const vec3<float> EyePos = {0, 0, 0};

int main() {

    // Load Assets
    Material m1{
        {0.1, 0.1, 0.1}, // Ambient
        {0.5, 0.3, 0.2}, // Diffuse
        {0.7, 0.3, 0.4}, // Specular
    };
    Material m2{
        {0.2, 0.2, 0.2}, // Ambient
        {0.2, 0.3, 0.5}, // Diffuse
        {0.4, 0.1, 0.5}, // Specular
    };
    Material m3{
        {0.1, 0.1, 0.1},
        {0.7, 0.7, 0.7},
        {0.1, 0.1, 0.1},
    };

    std::vector<Object *>
        objects;
    // std::array<std::array<Color<uint8_t>, WIDTH>, HEIGHT> pixel_data;
    PPM<Color<uint8_t>> Image(Width, Height);

    Sphere obj1({0.5, -0.5, -4}, 0.5, m1);
    Sphere obj2({-0.5, -0.7, -4}, 0.3, m2);
    Triangle obj3({1 * TriangleSize, -1, 1 * TriangleSize},
                  {-1 * TriangleSize, -1, 1 * TriangleSize},
                  {1 * TriangleSize, -1, -1 * TriangleSize}, m3);
    Triangle obj4({-1 * TriangleSize, -1, 1 * TriangleSize},
                  {-1 * TriangleSize, -1, -1 * TriangleSize},
                  {1 * TriangleSize, -1, -1 * TriangleSize}, m3);
    objects.push_back(&obj1);
    objects.push_back(&obj2);
    objects.push_back(&obj3);
    objects.push_back(&obj4);

    // Build Light
    std::vector<Light *> lights;
    PointLight light0{{1, 1, -2}, {0.9, 0.9, 0.9}};
    AmbientLight light1{{0.4, 0.6, 0.5}};
    lights.push_back(&light0);
    lights.push_back(&light1);

    // RayTracing
    for (int row = 0; row < Height; row++)
        for (int col = 0; col < Width; col++) {
            // 1. pixel -> image position
            // int x = row - HEIGHT / 2;
            // int y = col - WIDTH / 2;
            // x = -x; // Keep loop index  consistency with image position

            // int x = (HEIGHT - row) - HEIGHT / 2;
            // int y = col - WIDTH / 2;

            // // 2. Generate Ray Map to Frame Coordination
            // float u = x * P_HEIGHT;
            // float v = y * P_WIDTH;

            // 1. piexl -> image position
            float u = L + (R - L) * col / (float)Width;
            float v = B + (T - B) * row / (float)Height;

            float w = -Focal;
            vec3<float> dir = normalize(vec3<float>{u, v, w});

            Ray ray(EyePos, dir);

            // 3. Loop Objects find closet hit
            HitRecord closest_ret{{}, INFINITY, {}};
            for (const auto &item : objects) {
                HitRecord info = item->hit(ray, 0.001, 10);
                if (info.t < closest_ret.t)
                    closest_ret = info;
            }

            // 4. Light Shading
            Color<float> color;
            if (closest_ret.t < INFINITY) {
                for (const auto &light : lights) {
                    auto tmp = light->illuminate(ray, closest_ret);
                    color = color + tmp;
                }
            } else {
                color = DefaultColor;
            }

            // 5. Set Pixel Color
            Color<uint8_t> pixel_color(color.r * 255, color.g * 255,
                                       color.b * 255, 255);
           
            Image.set(Height - row - 1, col, pixel_color);
        }

    Image.save("image.ppm");
    std::cout << "Done" << std::endl;
    return 0;
}