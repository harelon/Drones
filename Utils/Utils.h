#ifndef UTILS_LIB_H
#define UTILS_LIB_H

#include <Arduino.h>

typedef enum {
  MAIN_NONE =   0x000000,
  MAIN_RED =    0xFF0000,
  MAIN_GREEN =  0x00FF00,
  MAIN_BLUE =   0x0000FF,
  MAIN_WHITE = 0xFFFFFF,
  MAIN_INTERMEDIATE = 0x000001,
} MainColors;

typedef enum {
    SERVO_RED = 0,
    SERVO_GREEN = 1,
    SERVO_BLUE = 2,
} ServoColors;

typedef enum{
    NOT_LOADED = 0,
    NEED_TO_LOAD = 1,
    LOADED = 2,
    DROPPED = 3,
} BallStates;

typedef struct {
  uint16_t r;
  uint16_t g;
  uint16_t b;
} rgbColor;

typedef struct{
   int16_t pitch;
   int16_t roll;
   int16_t yaw;
} AngularOrientation;

class Utils
{
    public:
        static MainColors RGB2MainColor(uint16_t r, uint16_t g, uint16_t b);
    private:
        Utils(){};
};

#endif
