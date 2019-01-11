#include <Ultrasonic.h>
#include "Adafruit_NeoPixel.h"
#define NumberOfWings 4
#define FrontRightPort 5
#define FrontLeftPort 6
#define BackRightPort 7
#define BackLeftPort 8
#define NumberOfLedsOnWing 4
#define StartLed 0
#define EchoPort 9
#define TrigPort 10
#define meters 100
#define BLACK Adafruit_NeoPixel::Color(0,0,0)
int LedPorts[NumberOfLedsOnWing] = {FrontRightPort, FrontLeftPort, BackRightPort, BackLeftPort};
Ultrasonic sensor(TrigPort,EchoPort);
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
  for (int i = 0; i < NumberOfWings; i++)
  {
    WingsLeds[i].fill(PixelColor, StartLed, Count);
    WingsLeds[i].fill(BLACK, Count, NumberOfLedsOnWing - Count);
    WingsLeds[i].show();
  }
  delay(1000);
}
