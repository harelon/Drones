#ifndef Drone_H
#define Drone_H

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include <CustomGyro.h>
#include <Comms.h>
#include <CustomLed.h>

class Drone: public Comms
{
    private:
        HDC1080JS _TempSensor;
        byte _echo;
        MainColors _sensedColor;
        CustomLed _cl;
        CustomGyro _Gyro;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 65535.0 / 37889.0;
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
        int _buzzerId;

    protected:
        void virtual OnTemperatureRequest();
        void virtual OnColorRequest();
        void virtual OnRawColorRequest();
        void virtual OnHeightRequest();
        void virtual OnBuzzerOnRequest();
        void virtual OnBuzzerOffRequest();
        void virtual OnAngularOrientationRequest();

        void SendTemperature();
        void SendColor();
        void SendRawColor();
        void SendHeight();
        void TurnBuzzerOn();
        void TurnBuzzerOff();
        void SendAngularOrientation();

        void ReadColor();
        void DispatchMessage(MessageHeader* message) override;

    public:
        Drone(uint8_t rx, uint8_t tx);
        Drone* SetUpTempSensor();
        Drone* SetUpColorSensor();
        Drone* SetUpHeightSensor(byte echo);
        Drone* SetUpBuzzer(byte buzzerId);
        Drone* SetUpGyro();
        Drone* SetUpLeds(byte pin);
        void TurnLedsOff();
};
#endif
