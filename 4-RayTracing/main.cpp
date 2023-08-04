#include "../Common/common.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include <array>
#include <cmath>
#include <vector>

const int WIDTH = 1024;
const int HEIGHT = 768;
const float FOCAL = 0.005;
const float P_WIDTH = 3.45 * 1e-6;
const float P_HEIGHT = 3.45 * 1e-6;
const Color<float> DEFAULT_COLOR = {0.411, 0.411, 0.411};

int main() {

    // Load Assets
    Material m1{};
    Material m2{};

    std::vector<Object *> objects;
    // std::array<std::array<Color<uint8_t>, WIDTH>, HEIGHT> pixel_data;
    PPM<Color<uint8_t>> Image(WIDTH, HEIGHT);

    Sphere obj1({0, 0, -4}, 0.5, m1);
    Sphere obj2({1, 2, -4}, 0.3, m2);
    objects.push_back(&obj1);
    objects.push_back(&obj2);

    // Build Light
    std::vector<Light *> lights;
    PointLight light0{{2, 2, -3}, {1, 1, 1}};
    AmbientLight light1{{0.2, 0.3, 0.1}};
    lights.push_back(&light0);
    lights.push_back(&light1);

    // RayTracing
    for (int row = 0; row < HEIGHT; row++)
        for (int col = 0; col < WIDTH; col++) {
            // 1. pixel -> image position
            int x = row - HEIGHT / 2;
            int y = col - WIDTH / 2;
            y = -y; // Keep loop index  consistency with image position

            // 2. Generate Ray Map to Frame Coordination
            float u = x * P_HEIGHT;
            float v = y * P_WIDTH;
            float w = -FOCAL;

            Ray ray({0, 0, 0}, normalize(vec3<float>{u, v, w}));

            // 3. Loop Objects find closet hit
            HitRecord closest_ret{{}, INFINITY, {}};
            for (const auto &item : objects) {
                HitRecord info = item->hit(ray, 0.001, 10);
                if (info.t < closest_ret.t)
                    closest_ret = info;
            }

            // 4. Light Shading
            Color<float> color = DEFAULT_COLOR;
            if (closest_ret.t < INFINITY) {
                for (const auto &light : lights) {
                    Color<float> color =
                        color + light->illuminate(ray, closest_ret);
                }
            }

            // 5. Set Pixel Color
            Color<uint8_t> pixel_color(color.r * 255, color.g * 255,
                                       color.b * 255, 255);
            Image.set(row, col, pixel_color);
        }

    Image.save("image.ppm");
}