#include <SoftwareSerial.h>
#define echoPin 13
// a library we made to usu adafruit neopixel easier to use
#include <CustomLed.h>

SoftwareSerial softSerial(6, 5);
CustomLed cl(7);
uint32_t color;
int distance;
byte radius;
byte lastRadius;

void setup()
{
  pinMode(echoPin, INPUT);
  softSerial.begin(9600);
  Serial.begin(9600);
  cl.begin();
  cl.TurnOffLed();
  color = 0;
  radius = 0;
  lastRadius = 0;
}

void loop()
{  
  distance = readDist();  
  Serial.println(distance);
  if(distance > 650)
  {
    radius = 0;
    return;
  }
  // get the most significant byte of the distance
  byte hd = distance >> 8;
  // get the least significant byte of the distance
  byte ld = distance & 0xFF;
  // send the most significant byte of the distance
  softSerial.write(hd);
  // send the least significant byte of the distance
  softSerial.write(ld);
  if (distance > 300)
  {
    color = Adafruit_NeoPixel::Color(255, 80 , 0);
    radius = 4;
  }
  else if (distance > 200)
  {
    color = Adafruit_NeoPixel::Color(0, 0 , 255);
    radius = 3;

  }
  else if (distance > 100)
  {
    color = Adafruit_NeoPixel::Color(0, 255, 0);
    radius = 2;
  }
  else if (distance > 0)
  {
    color = Adafruit_NeoPixel::Color(255, 0, 0);
    radius = 1;
  }
  // no need to turn off the leds if the next ring radius is bigger because it will
  // override the leds that were lit on the the last radius
  // if the current radius is smaller we need to turn off the leds so we won't have
  // leftovers from the last ring that was lit
  if (radius < lastRadius)
  {
    cl.TurnOffLed();
  }
  if (radius != lastRadius)
  {
    // if the color needs changing then set the rings that color
    cl.SetRing(color, radius);
  }
  lastRadius = radius;
  delay(1000);  
}

int readDist()
{
  // reads distance
  return pulseIn(echoPin, HIGH) / 58;
}
