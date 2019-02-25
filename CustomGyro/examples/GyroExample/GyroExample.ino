#include <CustomGyro.h>
#include <Wire.h>
CustomGyro gyro;
void setup()
{
    Serial.begin(9600);
    Wire.begin();
    gyro.begin();
}

void loop()
{
    Serial.print("pitch = ");
    Serial.println(gyro.GetPitch());
    Serial.print("roll = ");
    Serial.println(gyro.GetRoll());
    Serial.print("current yaw = ");
    Serial.println(gyro.GetYaw());
}
