#ifndef CustomLed_H
#define CustomLed_H
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DEFAULT_PIN 7
#define NUMBER_OF_LEDS 16
#define NUMBER_OF_WINGS 4
#define LED_RED Adafruit_NeoPixel::Color(255,0,0)
#define LED_GREEN Adafruit_NeoPixel::Color(0,255,0)
#define LED_BLUE Adafruit_NeoPixel::Color(0,0,255)
#define LED_ORANGE Adafruit_NeoPixel::Color(255,127,0)

class CustomLed
{
    private:
        int _pin;
        Adafruit_NeoPixel strip;
    public:
        CustomLed(int pin);
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
        bool SetAll(byte redValue, byte greenValue, byte blueValue);
        void SetAll(uint32_t color);
        void TurnOffLed();
};

#endif
