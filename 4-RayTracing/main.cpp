#include "../Common/common.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

const int WIDTH = 1024;
const int HEIGHT = 768;
const float FOCAL = 0.005;
const float L = -3.45 * 1e-6 * WIDTH / 2;
const float R = 3.45 * 1e-6 * WIDTH / 2;
const float T = 3.45 * 1e-6 * HEIGHT / 2;
const float B = -3.45 * 1e-6 * HEIGHT / 2;
const Color<float> DEFAULT_COLOR = {0.411, 0.411, 0.411};

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

    std::vector<Object *> objects;
    // std::array<std::array<Color<uint8_t>, WIDTH>, HEIGHT> pixel_data;
    PPM<Color<uint8_t>> Image(WIDTH, HEIGHT);

    Sphere obj1({0.5, 0.5, -4}, 0.5, m1);
    Sphere obj2({-0.5, 0.3, -4}, 0.3, m2);
    objects.push_back(&obj1);
    objects.push_back(&obj2);

    // Build Light
    std::vector<Light *> lights;
    PointLight light0{{2, 2, 0}, {0.9, 0.9, 0.9}};
    AmbientLight light1{{0.2, 0.3, 0.1}};
    lights.push_back(&light0);
    lights.push_back(&light1);

    // RayTracing
    for (int row = 0; row < HEIGHT; row++)
        for (int col = 0; col < WIDTH; col++) {
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
            float u = L + (R - L) * col / (float)WIDTH;
            float v = B + (T - B) * row / (float)HEIGHT;

            float w = -FOCAL;
            vec3<float> dir = normalize(vec3<float>{u, v, w});

            Ray ray({0, 0, 0}, dir);

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
                color = DEFAULT_COLOR;
            }

            // 5. Set Pixel Color
            Color<uint8_t> pixel_color(color.r * 255, color.g * 255,
                                       color.b * 255, 255);
           
            Image.set(HEIGHT - row - 1, col, pixel_color);
        }

    Image.save("image.ppm");
    std::cout << "Done" << std::endl;
    return 0;
}