#include <CustomLed.h>

CustomLed::CustomLed(byte pin)
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
    strip.updateLength(NUMBER_OF_LEDS);
    strip.setPin(_pin);
    strip.begin();
}

void CustomLed::SetPin(byte pin)
{
    _pin = pin;
}

bool CustomLed::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte stopWing, byte stopLed)
{
    return SetLeds(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue), startWing, startLed, stopWing, stopLed);
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
    fill(color, realStartLed, NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte numberOfLeds)
{
   return SetLeds(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue), startWing, startLed, numberOfLeds);
}

bool CustomLed::SetLeds(uint32_t color, byte startWing, byte startLed, byte numberOfLeds)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_WINGS * (startWing - 1);
    if (realStartLed < 0 || realStartLed > 15)
    {
        return false;
    }
    fill(color, realStartLed, numberOfLeds);
    strip.show();
    return true;
}

bool CustomLed::SetLed(byte redValue, byte greenValue, byte blueValue, byte wing, byte led)
{
    return SetLed(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue), wing, led);
}

bool CustomLed::SetLed(uint32_t color, byte wing, byte led)
{
    byte realLed = led - 1 + NUMBER_OF_WINGS * (wing - 1);
    if (realLed < 0 || realLed > 15) 
    {
        return false;
    }
    fill(color, realLed, 1);
    strip.show();
    return true;
}

bool CustomLed::SetWing(byte redValue, byte greenValue, byte blueValue, byte wing)
{
    return SetWing(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue), wing);
}

bool CustomLed::SetWing(uint32_t color, byte wing)
{
    if (wing < 1 || wing > 4)
    {
        return false;
    }
    byte startLed = NUMBER_OF_WINGS * (wing - 1);
    fill(color, startLed, 4);
    strip.show();
    return true;
}

bool CustomLed::SetRing(byte redValue, byte greenValue, byte blueValue, byte radius)
{
    return SetRing(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue), radius);
}

bool CustomLed::SetRing(uint32_t color, byte radius)
{
    if (radius < 1 || radius > 4)
    {
        return false;
    }
    for(byte i = 0; i < 4; i++)
    {
        fill(color, i * 4, radius);
    }
    strip.show();
    return true;
}

void CustomLed::SetAll(byte redValue, byte greenValue, byte blueValue)
{
    SetAll(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue));
}

void CustomLed::SetAll(uint32_t color)
{
    fill(color, 0, NUMBER_OF_LEDS);
    strip.show();
}

void CustomLed::TurnOffLed()
{
    strip.clear();
    strip.show();
}

void CustomLed::fill(uint32_t c, uint16_t first, uint16_t count) {
  uint16_t i, end;

  if(first >= NUMBER_OF_LEDS) {
    return; // If first LED is past end of strip, nothing to do
  }

  // Calculate the index ONE AFTER the last pixel to fill
  if(count == 0) {
    // Fill to end of strip
    end = NUMBER_OF_LEDS;
  } else {
    // Ensure that the loop won't go past the last pixel
    end = first + count;
    if(end > NUMBER_OF_LEDS) end = NUMBER_OF_LEDS;
  }

  for(i = first; i < end; i++) {
    strip.setPixelColor(i, c);
  }
}
