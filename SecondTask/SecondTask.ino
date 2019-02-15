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
  //initialize light sensor and enable it
  for (int i = 0; i < NumberOfWings; i++)
  {
    WingsLeds[i]= Adafruit_NeoPixel(NumberOfLedsOnWing,LedPorts[i],NEO_GRB+ NEO_KHZ800);
    WingsLeds[i].begin();    
  }
  Serial.begin(9600);
}
void loop()
{
  if(!LightSensor.readRedLight(red_light)||
  !LightSensor.readGreenLight(green_light)||
  !LightSensor.readBlueLight(blue_light))
  {
    return;
  }
  red_light = red_light * TransmitionRate;
  green_light = green_light * TransmitionRate;
  blue_light = blue_light * TransmitionRate;
  // reads colors from the light sensor
  sensedColor = detectMainColor(red_light, green_light, blue_light);
  // call which determine what color the light that is read
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
    //if the light read isn't what the wing is supposed to show turn off her light
    if (&WingsLeds[i] != Wing)
    {
      WingsLeds[i].fill(BLACK, StartLed, NumberOfLedsOnWing);
      WingsLeds[i].show();
    }
  }
  // if the color sensed match any color then Wing will be equal to something and it will turn on her light
  if (Wing != nullptr)
  {
    Wing->fill(PixelColor, StartLed, NumberOfLedsOnWing);
    Wing->show();
  }
  // reset wing because next time you need to call the function and have a different wing
  Wing = nullptr;
}

MainColors detectMainColor(uint16_t r, uint16_t g, uint16_t b)
{
  //transform color to hsv beacuse it is easier to determine which color it is
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
  // if the color has low light return none which means low light
  if (Cmax < 0.4)
  {
    return NONE;
  }
  // if the color has low saturation it is white then return white
  if (d / Cmax < 0.4)
  {
    return WHITE;
  }
  // the hue range for green in hsv
  if (h < 180 && h > 90)
  {
    return GREEN;
  }
  // the hue range for blue in hsv
  else if (h < 255 && h > 200)
  {
    return BLUE;
  }
  // the hue range for red in hsv
  else if ((h > 345 && h < 360) || ( h < 11 && h > 0))
  {
    return RED;
  }  
}
// needed for hsv conversion
float Max(float a, float b)
{
  if (a > b)
  {
    return a;
  }
  return b;
}
// needed for hsv conversion
float Min(float a, float b)
{
  if (a < b)
  {
    return a;
  }
  return b;
}
