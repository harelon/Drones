#ifndef Drone_H
#define Drone_H

#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include "Adafruit_NeoPixel.h"

#include <Comms.h>

#define NumberOfWings 4
#define NumberOfLedsOnWing 4
#define FrontRight 0
#define FrontLeft 1
#define BackRight 2
#define BackLeft 3
#define StartLed 0
#define BLACK Adafruit_NeoPixel::Color(0,0,0)

class Drone: public Comms
{   
    private:
        HDC1080JS _TempSensor;
        int _echo;
        int _trig;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 65535.0 / 37889.0;
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
        int _buzzerId;
        int LedPorts[NumberOfWings];
        Adafruit_NeoPixel WingsLeds[NumberOfWings];
    protected:
        void virtual OnColorRequest();
        void virtual OnTemperatureRequest();
        void virtual OnHeightRequest();
        void virtual OnBuzzerOnRequest();
        void virtual OnBuzzerOffRequest();
        void SendTemperature();
        void SendColor();
        void SendHeight();
<<<<<<< HEAD
        void TurnBuzzerOn();
        void TurnBuzzerOff();
=======
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
        void DispatchMessage(MessageHeader* message) override;
    public:
        Drone(uint8_t rx, uint8_t tx);
        Drone* SetUpTempSensor();
        Drone* SetUpColorSensor();
        Drone* SetUpHeightSensor(int echo, int trig);
        Drone* SetUpBuzzer(int buzzerId);
        Drone* SetUpLeds(int FrontRightPort, int FrontLeftPort, int BackRightPort, int BackLeftPort);
        void TurnLedsOff();
};
#endif
