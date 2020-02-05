#include <CustomLedV2.h>

CustomLedV2::CustomLedV2(byte pin)
{
    _pin = pin;
}

CustomLedV2::CustomLedV2()
{
    _pin = DEFAULT_PIN;
}

void CustomLedV2::begin()
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

void CustomLedV2::SetPin(byte pin)
{
    _pin = pin;
}

bool CustomLedV2::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startRing, byte startLed, byte stopRing, byte stopLed)
{
    return SetLeds(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue), startRing, startLed, stopRing, stopLed);
}

bool CustomLedV2::SetLeds(uint32_t color, byte startRing, byte startLed, byte stopRing, byte stopLed)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_RINGS * (startRing - 1);
    byte realStoptLed = stopLed  + NUMBER_OF_RINGS * (stopRing - 1);
    byte NunmberOfLeds = realStoptLed - realStartLed;
    if(realStartLed >= realStoptLed || realStartLed > (NUMBER_OF_LEDS - 1) || realStartLed < 0 || realStoptLed > (NUMBER_OF_LEDS - 1) || realStoptLed < 0)
    {
        return false;
    }
    fill(color, realStartLed, NunmberOfLeds);
    strip.show();
    return true;
}

bool CustomLedV2::SetLeds(byte redValue, byte greenValue, byte blueValue, byte startRing, byte startLed, byte numberOfLeds)
{
   return SetLeds(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue), startRing, startLed, numberOfLeds);
}

bool CustomLedV2::SetLeds(uint32_t color, byte startRing, byte startLed, byte numberOfLeds)
{
    byte realStartLed = startLed - 1 + NUMBER_OF_RINGS * (startRing - 1);
    if (realStartLed < 0 || realStartLed > (NUMBER_OF_LEDS - 1))
    {
        return false;
    }
    fill(color, realStartLed, numberOfLeds);
    strip.show();
    return true;
}

bool CustomLedV2::SetLed(byte redValue, byte greenValue, byte blueValue, byte ring, byte led)
{
    return SetLed(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue), ring, led);
}

bool CustomLedV2::SetLed(uint32_t color, byte ring, byte led)
{
    byte realLed = led - 1 + NUMBER_OF_RINGS * (ring - 1);
    if (realLed < 0 || realLed > (NUMBER_OF_LEDS - 1)) 
    {
        return false;
    }
    fill(color, realLed, 1);
    strip.show();
    return true;
}

bool CustomLedV2::SetRing(byte redValue, byte greenValue, byte blueValue, byte ring)
{
    return SetRing(Adafruit_NeoPixel::Color(redValue,greenValue,blueValue), ring);
}

bool CustomLedV2::SetRing(uint32_t color, byte ring)
{
    if (ring < 1 || ring > NUMBER_OF_RINGS)
    {
        return false;
    }
    byte startLed = LEDS_ON_RING * (ring - 1);
    fill(color, startLed, LEDS_ON_RING);
    strip.show();
    return true;
}

void CustomLedV2::SetAll(byte redValue, byte greenValue, byte blueValue)
{
    SetAll(Adafruit_NeoPixel::Color(redValue, greenValue, blueValue));
}

void CustomLedV2::SetAll(uint32_t color)
{
    fill(color, 0, NUMBER_OF_LEDS);
    strip.show();
}

void CustomLedV2::TurnOffLed()
{
    strip.clear();
    strip.show();
}

void CustomLedV2::fill(uint32_t c, uint16_t first, uint16_t count) {
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