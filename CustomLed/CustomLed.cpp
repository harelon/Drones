#include <CustomLed.h>

CustomLed::CustomLed(char pin)
{
    *_pin = pin;
}

CustomLed::CustomLed()
{
    *_pin = DEFAULT_PIN;
}

void CustomLed::begin()
{
    strip = Adafruit_NeoPixel(16,*_pin, NEO_GRB + NEO_KHZ800);
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000)
            clock_prescale_set(clock_div_1)
    #endif
    strip.begin();
}

bool CustomLed::SetLeds(char redValue, char greenValue, char blueValue, char startWing, char startLed, char stopWing, char stopLed)
{
    char realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    char realStoptLed = stopLed - 1  + NUMBER_OF_WINGS * (stopWing - 1);
    if(realStartLed >= realStoptLed || realStartLed > 15 || realStartLed < 0 || realStoptLed > 15 || realStoptLed < 0)
    {
        return false;
    }
    for(char i = realStartLed; i <= realStopLed; i++)
    {
        strip.setPixelColor(i, redValue, greenValue, blueValue);
    }
    strip.show();
    return true;
}

bool CustomLed::SetLeds(char redValue, char greenValue, char blueValue, char startWing, char startLed, char NunmberOfLeds)
{
    char realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    if (realStartLed < 0 || realStartLed < 15)
    {
        return false;
    }
    for(char i = realStartLed; i <= realStartLed + NunmberOfLeds; i++)
    {
        strip.setPixelColor(i, redValue, greenValue, blueValue);
    }
    strip.show();
    return true;
}

bool CustomLed::SetLed(char redValue, char greenValue, char blueValue, char wing, char led)
{
    char realLed = led - 1 + NUMBER_OF_WINGS * (wing - 1);
    if (realLed < 0 || realLed < 15) 
    {
        return false;
    }
    strip.setPixelColor(realLed, redValue, greenValue, blueValue);
    strip.show();
    return true;
}

void CustomLed::TurnOffLed()
{
    strip.clear();
    strip.show();
}
