#include <MPU6050.h>
#include <Wire.h>
#include <math.h>
#include <CustomLed.h>
MPU6050 Gyro;
int16_t gx;
int16_t gy;
int16_t gz;
int16_t ax;
int16_t ay;
int16_t az;
#define gyroScale 131
CustomLed customLed(7);
void setup()
{
  Serial.begin(9600);  
  Wire.begin();
  Gyro.initialize();  
  customLed.begin();
  customLed.TurnOffLed();
  Serial.println("setup succeeded");
}
void loop()
{
    customLed.TurnOffLed();
    Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    Serial.println(gz/gyroScale);  
    if(gz/gyroScale > 15)
    {
        customLed.SetAll(LED_GREEN);
    }
    else if (gz/gyroScale < (-15))
    {
        customLed.SetAll(LED_BLUE);
    }    
    delay(500);
}
