#ifndef CustomLed_H
#define CustomLed_H
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DEFAULT_PIN 7
#define NUMBER_OF_LEDS 16
#define NUMBER_OF_WINGS 4
#define LEDS_ON_WING 4
#define LED_RED 0xFF0000
#define LED_GREEN 0x00FF00
#define LED_BLUE 0x0000FF
#define LED_ORANGE 0xFF7F00
#define LED_YELLOW 0xFFFF00
#define LED_PURPLE 0x7F00FF
#define LED_WHITE 0xFFFFFF

class CustomLed
{
    private:
        byte _pin;
        Adafruit_NeoPixel strip;
        void fill(uint32_t c, uint16_t first, uint16_t count);
    public:
        CustomLed(byte pin);
        CustomLed();
        void SetPin(byte pin);
        void begin();
        bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte stopWing, byte stopLed);
        bool SetLeds(uint32_t color, byte startWing, byte startLed, byte stopWing, byte stopLed);
        bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte numberOfLeds);
        bool SetLeds(uint32_t color, byte startWing, byte startLed, byte numberOfLeds);
        bool SetLed(byte redValue, byte greenValue, byte blueValue, byte wing, byte led);
        bool SetLed(uint32_t color, byte wing, byte led);
        bool SetWing(byte redValue, byte greenValue, byte blueValue, byte wing);
        bool SetWing(uint32_t color, byte wing);
        bool SetRing(byte redValue, byte greenValue, byte blueValue, byte radius);
        bool SetRing(uint32_t color, byte radius);
        void SetAll(byte redValue, byte greenValue, byte blueValue);
        void SetAll(uint32_t color);
        void TurnOffLed();
};

#endif
