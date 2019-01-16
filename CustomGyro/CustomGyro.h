<<<<<<< HEAD
#include <MPU6050.h>
#include <math.h>

#define GyroScale 131
class CustomGyro
{
    private:
        MPU6050 _Gyro;
        int16_t ax;
        int16_t ay;
        int16_t az;
        int16_t gx;
        int16_t gy;
        int16_t gz;
        long _pitchError;
        long _rollError;
    public:
        CustomGyro();
        void begin();
        float GetPitch();
        float GetRoll();
        float GetYaw();
        void ResetPitchAndRoll();
};
=======
#ifndef CustomGyro_h
#define CustomGyro_h

#define SensorAdress 0x68

class CustomGyro
{
    public:
        CustomGyro();
    protected:
        void GetGyro();
        void GetAccelerometer();
    private:
        int16_t AcX;
        int16_t AcY;
        int16_t AcZ;
        int16_t GyX;
        int16_t GyY;
        int16_t GyZ;
        void Measure();
};

#endif
>>>>>>> CustomGyro library start
