#include "SparkFun_APDS9960.h"
#include "Adafruit_NeoPixel.h"
#define NumberOfWings 4
#define FrontRightPort 5
#define FrontLeftPort 6
#define BackRightPort 7
#define BackLeftPort 8
#define FrontRight 0
#define FrontLeft 1
#define BackRight 2
#define BackLeft 3
#define NumberOfLedsOnWing 4
#define StartLed 0
#define BLACK Adafruit_NeoPixel::Color(0,0,0)
#define TransmitionRate 255.0/37889.0
int LedPorts[NumberOfWings] = {FrontRightPort, FrontLeftPort, BackRightPort, BackLeftPort};
Adafruit_NeoPixel WingsLeds[NumberOfWings];
SparkFun_APDS9960 LightSensor;
uint32_t PixelColor;
uint16_t red_light;
uint16_t green_light;
uint16_t blue_light;
Adafruit_NeoPixel* Wing = nullptr;

typedef enum {
  NONE,
  RED,
  GREEN,
  BLUE,
  WHITE,
} MainColors;
MainColors sensedColor;



void setup()
{
  LightSensor.init();
  LightSensor.enableLightSensor(false);
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
  LightSensor.readRedLight(red_light);
  LightSensor.readGreenLight(green_light);
  LightSensor.readBlueLight(blue_light);
  red_light = red_light * TransmitionRate;
  green_light = green_light * TransmitionRate;
  blue_light = blue_light * TransmitionRate;
  sensedColor = detectMainColor(red_light, green_light, blue_light);
  Serial.println(sensedColor);
  if (sensedColor == WHITE)
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 255, 255);
    Wing = &WingsLeds[FrontRight];
  }
  if (sensedColor == RED)
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 0, 0);
    Wing = &WingsLeds[BackLeft];
  }
  else if (sensedColor == GREEN)
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 255, 0);
    Wing = &WingsLeds[BackRight];
  }
  else if (sensedColor == BLUE)
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 0, 255);
    Wing = &WingsLeds[FrontLeft];
  }
  for (int i = 0; i < NumberOfWings; i++)
  {
    if (&WingsLeds[i] != Wing)
    {
      WingsLeds[i].fill(BLACK, StartLed, NumberOfLedsOnWing);
      WingsLeds[i].show();
    }
  }
  if (Wing != nullptr)
  {
    Wing->fill(PixelColor, StartLed, NumberOfLedsOnWing);
    Wing->show();
  }
  Wing = nullptr;
}

MainColors detectMainColor(uint16_t r, uint16_t g, uint16_t b)
{
  float Rtag = r / 255.0;
  float Gtag = g / 255.0;
  float Btag = b / 255.0;
  float Cmax = Max(Rtag, Max(Gtag, Btag));
  float Cmin = Min(Rtag, Min(Gtag, Btag));
  float d = Cmax - Cmin;
  float h;
  if (d == 0)
  {
    h = 0;
  }
  else if (Cmax == Rtag)
  {
    h = 60 * ((Gtag - Btag) / d);
    if (h < 0)
    {
      h = h + 360;
    }
  }
  else if (Cmax == Gtag)
  {
    h = 60 * (((Btag - Rtag) / d) + 2);
  }
  else
  {
    h = 60 * (((Rtag - Gtag)) / d + 4);
  }
  Serial.print("H:");
  Serial.println(h);
  Serial.print("S:");
  Serial.println(d / Cmax);
  Serial.print("V:");
  Serial.println(Cmax);
  if (Cmax < 0.4)
  {
    return NONE;
  }
  if (d / Cmax < 0.6)
  {
    return WHITE;
  }
  if (h < 130 && h > 90)
  {
    return GREEN;
  }
  else if (h < 255 && h > 200)
  {
    return BLUE;
  }
  else if ((h > 345 && h < 360) || ( h < 11 && h > 0))
  {
    return RED;
  }
}

float Max(float a, float b)
{
  if (a > b)
  {
    return a;
  }
  return b;
}

float Min(float a, float b)
{
  if (a < b)
  {
    return a;
  }
  return b;
}
