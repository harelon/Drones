#include <SendToScreen.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include <Ultrasonic.h>
#define rLed 11
#define gLed 12
#define bLed 13
#define buzzerPort 8
// tone(buzzerPortPort,frequency) noTone(buzzerPortPort)
#define mainLightSize 4
#define rx 7
#define tx 6
float transmitionRate = 65536.0 / 37889.0;
rgbColor colors;
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
HDC1080JS tempSensor;
Ultrasonic ultrasonic(9, 10);
SoftwareSerial mySerial(6, 7);
requestOptions request;
int data;
float tempdata;
colorResult result;
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
int mainLight [mainLightSize] = {0, 0, 0, 0};
bool redLightShow = 0;
bool greenLightShow = 0;
bool blueLightShow = 0;
rgbColor convertRGB16toRGB888(uint16_t r, uint16_t g, uint16_t b)
{
  rgbColor returnColor;
  returnColor.r = (int)((float)(r & 0xFF00) * transmitionRate) >> 8;
  returnColor.g = (int)((float)(g & 0xFF00) * transmitionRate) >> 8;
  returnColor.b = (int)((float)(b & 0xFF00) * transmitionRate) >> 8;
  return returnColor;
}
String TransformToHex(uint8_t num)
{
  String returnString = "";
  returnString = String((num >> 4) & 0xF, HEX);
  returnString += String(num & 0xF, HEX);
  return returnString;
}

void LightUp(byte rVal, byte gVal, byte bVal)
{
  analogWrite(rLed, rVal);
  analogWrite(gLed, gVal);
  analogWrite(bLed, bVal);
}
void LightUp(bool c [] )
{

  digitalWrite(rLed, c[0]);
  digitalWrite(gLed, c[1]);
  digitalWrite(bLed, c[2]);
  if (c[3] == true)
  {
    digitalWrite(rLed, true);
    digitalWrite(gLed, true);
    digitalWrite(bLed, true);
  }
}
void setup() {
  pinMode(rx , INPUT);
  pinMode(tx, OUTPUT);
  // Initialize Serial port
  Serial.begin(9600);
  mySerial.begin(9600);
  apds.init();
  apds.enableLightSensor(false) ;
  tempSensor = HDC1080JS();
  tempSensor.config();
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(buzzerPort, OUTPUT);
  delay(500);
}

void loop() {
  Serial.println(transmitionRate);
  if (mySerial.available() > 0)
  {
    request = (requestOptions)mySerial.read();
    Serial.println(request);
  }
  switch (request)
  {
    case height:
      data = ultrasonic.distanceRead();
      break;
    case temp:
      tempSensor.readTempHumid();
      data = tempSensor.getTemp();
      break;
    case color:
      if (  !apds.readAmbientLight(ambient_light) ||
            !apds.readRedLight(red_light) ||
            !apds.readGreenLight(green_light) ||
            !apds.readBlueLight(blue_light) ) {
        return;
      }
      if (blue_light > red_light && blue_light > green_light)
      {
        data = blue;
      }
      else if (green_light > red_light && green_light > blue_light)
      {
        data = green;
      }
      else if (red_light > blue_light && red_light > green_light)
      {
        data = red;
      }
      else
      {
        data = white;
      }
      break;
    case buzzer:
      tone(buzzerPort, 800);
      break;
    default:
      data = 0;
      noTone(buzzerPort);
      delay(500);
      return;
  }
  Serial.println("data:" + String(data));
  mySerial.println(data);
  delay(500);
  // Wait 1 second before next reading

}
