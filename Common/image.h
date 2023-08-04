#include "color.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

template <typename T> class PPM {
  private:
    uint32_t width;
    uint32_t height;
    std::vector<T> data;

  public:
    PPM(uint32_t w, uint32_t h) : width(w), height(h) { data.resize(w * h); };

    void save(std::string path) {
        std::fstream output(path,std::ios::out);
        output << "P3\n";
        output << width << " " << height << "\n";
        output << "255\n";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                output << get(i, j).r << " " << get(i, j).g << " "
                       << get(i, j).b << "\n";
            }
        }
    }
    void set(uint32_t row, uint32_t col, T color) {
        data[row * width + col] = color;
    }
    T get(uint32_t row, uint32_t col) {
        return data[row * width + col];
    }
};
