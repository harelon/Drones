#include <CustomGyro.h>

CustomGyro::CustomGyro()
{

}

void CustomGyro::begin()
{
    _Gyro.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
    _Gyro.calibrateGyro();
    _Gyro.setThreshold(3);
}


float CustomGyro::GetYaw()
{
    return _yaw;
}

float CustomGyro::GetPitch()
{
    return _pitch;
}

float CustomGyro::GetRoll()
{
    return _roll;
}

void CustomGyro::startTime()
{
    _startTime = millis();
}

void CustomGyro::updateValues()
{
    Vector norm = _Gyro.readNormalizeGyro();

    _pitch = _pitch + norm.YAxis * timeStep;
    _roll = _roll + norm.XAxis * timeStep;
    _yaw = _yaw + norm.ZAxis * timeStep;
    delay((timeStep*1000) - (millis() - _startTime));
}
