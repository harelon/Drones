#include "SparkFun_APDS9960.h"
#include "Adafruit_NeoPixel.h"
#define NumberOfWings 4
#define FrontRightPort 1
#define FrontLeftPort 2
#define BackRightPort 3
#define BackLeftPort 4
#define FrontRight 0
#define FrontLeft 1
#define BackRight 2
#define BackLeft 3
#define NumberOfLedsOnWing 4
#define ColorDivisonFactor 1.5
#define ColorSubtractionFactor 10000
#define MaxColor 50000
#define StartLed 0
int LedPorts[NumberOfWings] = {FrontRightPort, FrontLeftPort, BackRightPort, BackLeftPort};
Adafruit_NeoPixel WingsLeds[NumberOfWings];
SparkFun_APDS9960 LightSensor;
uint32_t PixelColor;
uint16_t red_light;
uint16_t green_light;
uint16_t blue_light;
Adafruit_NeoPixel* Wing;
typedef enum{
  RED,
  GREEN,
  BLUE,
  WHITE,
}MainColors;

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
  if(red_light>MaxColor && green_light > MaxColor && blue_light )
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 255, 255);
    Wing = &WingsLeds[FrontRight];
  }
  if ((red_light / ColorDivisonFactor > green_light || red_light - ColorSubtractionFactor > green_light) && 
  (red_light / ColorDivisonFactor > blue_light || red_light - ColorSubtractionFactor > blue_light))
  {
    PixelColor = Adafruit_NeoPixel::Color(255, 0, 0);
    Wing = &WingsLeds[BackLeft];
  }
  else if ((green_light / ColorDivisonFactor > red_light || green_light - ColorSubtractionFactor > red_light) && 
  (green_light / ColorDivisonFactor > blue_light || green_light - ColorSubtractionFactor > blue_light))  
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 255, 0); 
    Wing = &WingsLeds[BackRight];    
  }
  else if ((blue_light / ColorDivisonFactor > red_light || blue_light - ColorSubtractionFactor > red_light) && 
  (blue_light / ColorDivisonFactor > green_light || blue_light - ColorSubtractionFactor > green_light))  
  {
    PixelColor = Adafruit_NeoPixel::Color(0, 0, 255);
    Wing = &WingsLeds[FrontLeft];
  }  
  Wing->fill(PixelColor, StartLed, NumberOfLedsOnWing);
}
