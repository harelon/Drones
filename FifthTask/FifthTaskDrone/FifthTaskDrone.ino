#include <SoftwareSerial.h>
#define echoPin 13
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
  byte hd = distance >> 8;
  byte ld = distance & 0xFF;
  softSerial.write(hd);
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
  if (radius < lastRadius)
  {
    cl.TurnOffLed();    
  }
  if (radius != lastRadius)
  {
    cl.SetRing(color, radius);
  }
  lastRadius = radius;
  delay(1000);  
}

int readDist()
{
  return pulseIn(echoPin, HIGH) / 58;
}
