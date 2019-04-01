#ifndef CustomGyro_h
#define CustomGyro_h

#include <MPU6050.h>

class CustomGyro
{
    private:
        MPU6050 _Gyro;
        float _pitch;
        float _roll;
        float _yaw;
        long _startTime;
        float _lastNormZ = 0;
        float _lastNormY = 0;
        float _lastNormX = 0;
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
