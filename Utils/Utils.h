#ifndef UTILS_LIB_H
#define UTILS_LIB_H

#include <Adafruit_NeoPixel.h>

class Utils
{
    public:
        static MainColors RGB2MainColor(uint16_t r, uint16_t g, uint16_t b);
    private:
        Utils(){};
};

typedef enum {
  NONE = Adafruit_NeoPixel::Color(0, 0, 0),
  RED = Adafruit_NeoPixel::Color(255, 0, 0),
  GREEN = Adafruit_NeoPixel::Color(0, 255, 0),
  BLUE = Adafruit_NeoPixel::Color(0, 0, 255),
  WHITE = Adafruit_NeoPixel::Color(255, 255, 255),
} MainColors;
#endif
