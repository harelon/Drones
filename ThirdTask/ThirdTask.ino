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
CustomLed customLed(7);
int wingNum;
long pitchError;
long rollError;
int changeValue = 30;
void setup()
{
  Serial.begin(9600);  
  Wire.begin();
  Gyro.initialize();
  resetPitchAndRoll();
  customLed.begin();
  Serial.println("setup succeeded");
}
void loop()
{  
  Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  customLed.TurnOffLed();
  wingNum = GetOrientedWing(changeValue);
  Serial.print("wingNum = ");
  Serial.println(wingNum);
  customLed.SetWing(LED_BLUE, (byte)wingNum);
  // clear leds
  delay(500);
}


double GetPitch()
{
  long azSquared = az;
  azSquared = azSquared * az;
  long aySquared = ay;
  aySquared = aySquared * ay;
  long az_ay = azSquared + aySquared;
  return RAD_TO_DEG * atan(ax / sqrt(az_ay)) - pitchError;
}


double GetRoll()
{
  long azSquared = az;
  azSquared = azSquared * az;
  long axSquared = ax;
  axSquared = axSquared * ax;
  long az_ax = azSquared + axSquared;
  return RAD_TO_DEG * atan(ay / sqrt(az_ax)) - rollError;
}


void resetPitchAndRoll()
{
  long pitchSum = 0;
  long rollSum = 0;
  int count = 0;
  long destTime = millis() + 1000;
  long axSquared;
  long aySquared;
  long azSquared;
  long az_ax;
  long az_ay;
  while (millis() < destTime)
  {
    Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    azSquared = az;
    azSquared = azSquared * az;
    aySquared = ay;
    aySquared = aySquared * ay;
    az_ay = azSquared + aySquared;
    pitchSum += RAD_TO_DEG * atan(ax / sqrt(az_ay));
    az_ax = azSquared + axSquared;
    axSquared = ax;
    axSquared = axSquared * ax;
    rollSum += RAD_TO_DEG * atan(ay / sqrt(az_ax));
    count += 1;
  }
  pitchError = pitchSum / count;
  rollError = rollSum / count;
}


int GetOrientedWing(double changeValue)
{
  int right = GetRollOrientation(GetRoll(), changeValue);
  int front = GetPitchOrientation(GetPitch(), changeValue);
  if (front != 0 && right != 0)
  {
    int oSum = front + right;
    if (oSum == 2)
    {
      return 4;
    }
    else if (oSum == -2)
    {
      return 2;
    }
    else
    {
      if (front > right)
      {
        return 1;
      }
      else
      {
        return 3;
      }
    }
  }
  return 0;
}


int GetPitchOrientation(double pitch, double changeValue)
{
  if (pitch > changeValue)
  {
    return -1;
  }
  else if (pitch < -changeValue)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


int GetRollOrientation(double roll, double changeValue)
{
  if (roll > changeValue)
  {
    return 1;
  }
  else if (roll < -changeValue)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}
