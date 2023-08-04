#include "color.h"
#include <array>
#include <stdint.h>
#include <string>
#include <memory>

template<typename T>
class PPM{
private:
    uint32_t width;
    uint32_t height;

   
public:
    PPM(uint32_t w,uint32_t h) : 
        width(w),height(h){};
    
    void save(std::string path)
    {

    }
    void set(uint32_t row,uint32_t col,T color)
    {

    }   
    T get(uint32_t row,uint32_t col){
        // return 
    } 
};

