#ifndef CustomGyro_h
#define CustomGyro_h

#include <MPU6050.h>

#define timeStep 0.2
class CustomGyro
{
    private:
        MPU6050 _Gyro;
        float _pitch;
        float _roll;
        float _yaw;
        long _startTime;
    public:
        CustomGyro();
        void begin();
        float GetPitch();
        float GetRoll();
        float GetYaw();
        void startTime();
        void updateValues();
};
#endif
