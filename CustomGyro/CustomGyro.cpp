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
    _pitch = _pitch + ((_lastNormX + norm.XAxis) / 2) * ((millis()-_startTime)/1000.0);
    _roll =_roll + ((_lastNormY + norm.YAxis) / 2) * ((millis()-_startTime)/1000.0);
    _yaw = _yaw + ((_lastNormZ + norm.ZAxis) / 2) * ((millis()-_startTime)/1000.0);
    _lastNormZ = norm.ZAxis;
    _lastNormY = norm.YAxis;
    _lastNormX = norm.XAxis;
}
