#ifndef CustomLed_H
#define CustomLed_H
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DEFAULT_PIN 5
#define NUMBER_OF_LEDS 16
#define NUMBER_OF_WINGS 4

class CustomLed
{
    private:
        char *_pin;
        Adafruit_NeoPixel strip;
    public:
        CustomLed(char pin);
        CustomLed();
        void begin();
        bool SetLeds(char redValue, char greenValue, char blueValue, char startWing, char startLed, char stopWing, char stopLed);
        bool SetLed(char redValue, char greenValue, char blueValue, char wing, char led);
        void TurnOffLed();
};

#endif
