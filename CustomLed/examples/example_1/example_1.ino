/*
   A lib that helps with the Adafruit leds.

   Connect the led to 5v, gnd and a digital pin.

   Public commands:
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
    bool SetRing(byte redValue, byte greenValue, byte blueValue, byte startRadius, byte endRadius);
    bool SetRing(uint32_t color, byte startRadius, byte endRadius);
    void SetAll(byte redValue, byte greenValue, byte blueValue);
    void SetAll(uint32_t color);
    void TurnOffLed();

   Type the command begin() in setup.

   can replace the RGB value with const such as:
    LED_RED
    LED_GREEN
    LED_BLUE
    LED_ORANGE
    LED_YELLOW
    LED_PURPLE
    LED_WHITE

   Created 20/2/2019
   modified 7/3/2019
   By Yehonatan Refael Boltansky
*/

#include <CustomLed.h>

CustomLed strip(5);

void setup()
{
  strip.begin();
}

void loop()
{
  strip.SetLeds(255, 0, 0, 2, 3, 4, 1); //turn on light from the third led on the second wing to the first led in the fourth wing
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetLed(255, 127, 0, 1, 3); //turn on the third led in the first wing
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetWing(255, 0, 255, 3); // turn on the third wing
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetRing(0, 255, 255, 3); //turn on all first 3 led of every wing
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetRing(0, 255, 0, 2, 4); //turn on all the leds in radius between 2 and 4 from the center
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetAll(255,255,255);//turn on all wings
  strip.TurnOffLed();//turn off leds.
  delay(2000);
  strip.SetAll(LED_RED);//turn on all wings
  strip.TurnOffLed();//turn off leds.
  delay(2000);
}
