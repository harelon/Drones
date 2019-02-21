#include <CustomLed.h>

CustomLed::CustomLed(int pin)
{
    _pin = pin;
}

CustomLed::CustomLed()
{
    _pin = DEFAULT_PIN;
}

void CustomLed::begin()
{
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000)
            clock_prescale_set(clock_div_1)
    #endif
    strip.updateType(NEO_GRB + NEO_KHZ800);
    strip.updateLength(16);
    strip.setPin(_pin);
    strip.begin();    
}

bool CustomLed::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte stopWing, byte stopLed)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    byte realStoptLed = stopLed  + NUMBER_OF_WINGS * (stopWing - 1);
    byte NunmberOfLeds = realStoptLed - realStartLed;
    if(realStartLed >= realStoptLed || realStartLed > 15 || realStartLed < 0 || realStoptLed > 15 || realStoptLed < 0)
    {
        return false;
    }
    strip.fill(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue),realStartLed,NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLeds(uint32_t color, byte startWing, byte startLed, byte stopWing, byte stopLed)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    byte realStoptLed = stopLed  + NUMBER_OF_WINGS * (stopWing - 1);
    byte NunmberOfLeds = realStoptLed - realStartLed;
    if(realStartLed >= realStoptLed || realStartLed > 15 || realStartLed < 0 || realStoptLed > 15 || realStoptLed < 0)
    {
        return false;
    }
    strip.fill(color, realStartLed, NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte NunmberOfLeds)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    if (realStartLed < 0 || realStartLed > 15)
    {
        return false;
    }
    strip.fill(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue),realStartLed,NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLeds(uint32_t color, byte startWing, byte startLed, byte NunmberOfLeds)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    if (realStartLed < 0 || realStartLed > 15)
    {
        return false;
    }
    strip.fill(color, realStartLed, NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLed(byte redValue, byte greenValue, byte blueValue, byte wing, byte led)
{
    byte realLed = led - 1 + NUMBER_OF_WINGS * (wing - 1);
    if (realLed < 0 || realLed > 15) 
    {
        return false;
    }
    strip.fill(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue),realLed,1);
    strip.show();
    return true;
}

bool CustomLed::SetLed(uint32_t color, byte wing, byte led)
{
    byte realLed = led - 1 + NUMBER_OF_WINGS * (wing - 1);
    if (realLed < 0 || realLed > 15) 
    {
        return false;
    }
    strip.fill(color, realLed, 1);
    strip.show();
    return true;
}

bool CustomLed::SetWing(byte redValue, byte greenValue, byte blueValue, byte wing)
{
    if (wing < 1 || wing > 4)
    {
        return false;
    }
    byte startLed = NUMBER_OF_WINGS * (wing - 1);
    strip.fill(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue),startLed,4);
    strip.show();
    return true;
}

bool CustomLed::SetWing(uint32_t color, byte wing)
{
    if (wing < 1 || wing > 4)
    {
        return false;
    }
    byte startLed = NUMBER_OF_WINGS * (wing - 1);
    strip.fill(color, startLed, 4);
    strip.show();
    return true;
}

bool CustomLed::SetAll(byte redValue, byte greenValue, byte blueValue)
{
    strip.fill(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue),0,NUMBER_OF_LEDS);
    strip.show();
    return true;
}

bool CustomLed::SetAll(uint32_t color)
{
    strip.fill(color,0,NUMBER_OF_LEDS);
    strip.show();
    return true;
}

void CustomLed::TurnOffLed()
{
    strip.clear();
    strip.show();
}
