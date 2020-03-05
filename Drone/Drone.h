#ifndef Drone_H
#define Drone_H

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include <CustomGyro.h>
#include <Comms.h>
#include <CustomLedV2.h>
// #include <ServoBall.h>
#include <Servo.h>
// #define ServoNumbers 3
class Drone: public Comms
{
    private:
        HDC1080JS _TempSensor;
        byte _echo;
        MainColors _sensedColor;
        CustomLedV2 _cl;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 255.0 / 37889.0;
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
        int _buzzerId;
        uint16_t _height = 0;
        Servo ball;

    protected:
        void virtual SendConnectMsg();

        void virtual OnTemperatureRequest();
        void virtual OnColorRequest();
        void virtual OnRawColorRequest();
        void virtual OnHeightRequest();
        void virtual OnBuzzerOnRequest();
        void virtual OnBuzzerOffRequest();
        void virtual OnAngularOrientationRequest();
        void virtual OnBallDropRequest(ServoRequest* message);
        void virtual OnLedRequest(LedRequest* message);

        void SendTemperature();
        void SendColor();
        void SendRawColor();
        void SendHeight();
        void TurnBuzzerOn();
        void TurnBuzzerOff();
        void SendAngularOrientation();
        void SendBallDrop(ServoRequest* message);
        void SendSetLeds(LedRequest* message);
        void DropBall();
        void SetLeds(rgbColor color, byte wing);

        void ReadColor();
        void SenseHeight();
        void DispatchMessage(MessageHeader* message) override;

    public:
        #ifdef ARDUINO_BOARD
            Drone(uint8_t rx, uint8_t tx):Comms(rx, tx){Wire.begin();SendConnectMsg();}
        #else
            Drone():Comms(){Wire.begin();SendConnectMsg();}
        #endif
        Drone* SetUpTempSensor();
        Drone* SetUpColorSensor();
        Drone* SetUpHeightSensor(byte echo);
        Drone* SetUpBuzzer(byte buzzerId);
        Drone* SetUpGyro();
        // Drone* SetUpServo(byte pin, ServoColors color);
        // Drone* SetUpServo(byte pin, ServoColors color, BallStates state);
        Drone* SetUpServo(byte pin);
        Drone* SetUpLeds(byte pin);
        CustomGyro _Gyro;
};
#endif
