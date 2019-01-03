#include <Ultrasonic.h>
#include "Adafruit_NeoPixel.h"
#define NumberOfWings 4
#define FrontRightPort 1
#define FrontLeftPort 2
#define BackRightPort 3
#define BackLeftPort 4
#define NumberOfLedsOnWing 4
#define StartLed 0
#define EchoPort 9
#define ReadPort 10
#define meters 100
int LedPorts[NumberOfLedsOnWing] = {FrontRightPort, FrontLeftPort, BackRightPort, BackLeftPort};
Ultrasonic sensor(EchoPort, ReadPort);
Adafruit_NeoPixel WingsLeds[NumberOfWings];
uint32_t PixelColor;
uint16_t Count;
void setup()
{
  for (int i = 0; i < NumberOfWings; i++)
  {    
    WingsLeds[i].updateType(NEO_GRB + NEO_KHZ800);
    WingsLeds[i].updateLength(NumberOfLedsOnWing);
    WingsLeds[i].setPin(LedPorts[i]);
    WingsLeds[i].begin();
  }
}

void loop()
{
  int distance = sensor.distanceRead();

  if (distance > 3 * meters)
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 165, 0);
    Count = 4;
  }
  else if (distance > 2 * meters)
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 0, 255);
    Count = 3;
  }
  else if (distance > 1 * meters)
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 255, 0);
    Count = 2;
  }
  else
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 0, 0);
    Count = 1;
  }

  for (Adafruit_NeoPixel Wing : WingsLeds)
  {
    Wing.fill(PixelColor, StartLed, Count);
  }
}
