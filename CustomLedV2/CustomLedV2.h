#ifndef CustomLedV2_H
#define CustomLedV2_H
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DEFAULT_PIN A0
#define NUMBER_OF_RINGS 4
#define LEDS_ON_RING 12
#define NUMBER_OF_LEDS 48
#define LED_RED 0xFF0000
#define LED_GREEN 0x00FF00
#define LED_BLUE 0x0000FF
#define LED_ORANGE 0xFF7F00
#define LED_YELLOW 0xFFFF00
#define LED_PURPLE 0x7F00FF
#define LED_WHITE 0xFFFFFF

class CustomLedV2
{
    private:
        byte _pin;
        Adafruit_NeoPixel strip;
        void fill(uint32_t c, uint16_t first, uint16_t count);
    public:
        CustomLedV2(byte pin);
        CustomLedV2();
        void SetPin(byte pin);
        void begin();
        bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startRing, byte startLed, byte stopRing, byte stopLed);
        bool SetLeds(uint32_t color, byte startRing, byte startLed, byte stopRing, byte stopLed);
        bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startRing, byte startLed, byte numberOfLeds);
        bool SetLeds(uint32_t color, byte startRing, byte startLed, byte numberOfLeds);
        bool SetLed(byte redValue, byte greenValue, byte blueValue, byte ring, byte led);
        bool SetLed(uint32_t color, byte ring, byte led);
        bool SetRing(byte redValue, byte greenValue, byte blueValue, byte ring);
        bool SetRing(uint32_t color, byte ring);
        void SetAll(byte redValue, byte greenValue, byte blueValue);
        void SetAll(uint32_t color);
        void TurnOffLed();
};

#endif