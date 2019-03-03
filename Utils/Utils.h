#ifndef UTILS_LIB_H
#define UTILS_LIB_H

#include <Arduino.h>

typedef enum {
  MAIN_NONE =   0x000000,
  MAIN_RED =    0xFF0000,
  MAIN_GREEN =  0x00FF00,
  MAIN_BLUE =   0x0000FF,
  MAIN_ WHITE = 0xFFFFFF,
} MainColors;

class Utils
{
    public:
        static MainColors RGB2MainColor(uint16_t r, uint16_t g, uint16_t b);
    private:
        Utils(){};
};

#endif
