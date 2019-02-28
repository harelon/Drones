#ifndef Drone_H
#define Drone_H

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include "Adafruit_NeoPixel.h"
#include <CustomGyro.h>
#include <Comms.h>
#include <Utils.h>
#include <CustomLed.h>

class Drone: public Comms
{   
    private:
        HDC1080JS _TempSensor;
        int _echo;        
        CustomGyro _Gyro;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 65535.0 / 37889.0;
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
        int _buzzerId;
        MainColors _sensedColor;
        CustomLed _cl;
    protected:
        void virtual OnColorRequest();
        void virtual OnTemperatureRequest();
        void virtual OnHeightRequest();
        void virtual OnBuzzerOnRequest();
        void virtual OnBuzzerOffRequest();
        void virtual OnAngularOrientationRequest();
        void SendTemperature();
        void SendColor();
        void SendHeight();
        void TurnBuzzerOn();
        void TurnBuzzerOff();
        void SendAngularOrientation();
        MainColors ReadColor();
        void DispatchMessage(MessageHeader* message) override;
    public:
        Drone(uint8_t rx, uint8_t tx);
        Drone* SetUpTempSensor();
        Drone* SetUpColorSensor();
        Drone* SetUpHeightSensor(int echo, int trig);
        Drone* SetUpBuzzer(int buzzerId);
        Drone* SetUpGyro();
        Drone* SetUpLeds(byte pin);
        void TurnLedsOff();
};
#endif
