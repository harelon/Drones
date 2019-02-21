/*
   A lib that helps with the Adafruit leds.
   
   Connect the led to 5v, gnd and a digital pin.
   
   Defualt pin - 7.
   Use the command >>>CustomLed led()<<< to set to default pin.

   Public commands:
    bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte stopWing, byte stopLed);
    bool SetLeds(uint32_t color, byte startWing, byte startLed, byte stopWing, byte stopLed);
    bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte NunmberOfLeds);
    bool SetLeds(uint32_t color, byte startWing, byte startLed, byte NunmberOfLeds);
    bool SetLed(byte redValue, byte greenValue, byte blueValue, byte wing, byte led);
    bool SetLed(uint32_t color, byte wing, byte led);
    bool SetWing(byte redValue, byte greenValue, byte blueValue, byte wing);
    bool SetWing(uint32_t color, byte wing);
    void TurnOffLed();

   Type the command begin() in setup.

   Created 20/2/2019
   By Yehonatan Refael Boltansky
*/

#include <CustomLed.h>

#define pin 5

CustomLed led(pin);

void setup()
{
  led.begin();
}

void loop()
{
}
