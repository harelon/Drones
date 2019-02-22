#include <CustomGyro.h>

CustomGyro::CustomGyro()
{

}

void CustomGyro::begin()
{
    if (TWCR == 0)
    {
        Wire.begin();   
    }  
    _Gyro.initialize();
    ResetPitchAndRoll();
}

float CustomGyro::GetYaw()
{
    _Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    return gz / GyroScale;
}

float CustomGyro::GetPitch()
{
    _Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    long azSquared = az;
    azSquared = azSquared * az;
    long aySquared = ay;
    aySquared = aySquared * ay;
    long az_ay = azSquared + aySquared;
    return RAD_TO_DEG * atan(ax / sqrt(az_ay)) - _pitchError;
}


float CustomGyro::GetRoll()
{
    _Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    long azSquared = az;
    azSquared = azSquared * az;
    long axSquared = ax;
    axSquared = axSquared * ax;
    long az_ax = azSquared + axSquared;
    return RAD_TO_DEG * atan(ay / sqrt(az_ax)) - _rollError;
}


void CustomGyro::ResetPitchAndRoll()
{
    long pitchSum = 0;
    long rollSum = 0;
    int count = 0;
    long axSquared;
    long aySquared;
    long azSquared;
    long az_ax;
    long az_ay;
    long destTime = millis() + 500;
    while (millis() < destTime)
    {
        _Gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
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
    _pitchError = pitchSum / count;
    _rollError = rollSum / count;
}
