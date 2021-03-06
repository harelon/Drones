#ifndef Controller_H
#define Controller_H

#include "Comms.h"

class Controller : public Comms
{
    protected:
        void virtual DispatchMessage(MessageHeader* message);
        void RequestForTemperature();
        void RequestRawColor();
        void RequestForColor();
        void RequestForHeight();
        void RequestForBuzzOn();
        void RequestForBuzzOff();
        void RequestForGyro();
        void RequestForServoDrop(ServoColors color);
        bool DroneConnected = false;

        void virtual OnDroneConnected() = 0;
        void virtual OnTemperatureResponse(TemperatureResponse* message) = 0;
        void virtual OnColorResponse(ColorResponse* message) = 0;
        void virtual OnRawColorResponse(RawColorResponse* message) = 0;
        void virtual OnHeightResponse(HeightResponse* message) = 0;
        void virtual OnBuzzResponse(BuzzResponse* message) = 0;
        void virtual OnGyroResponse(GyroResponse* message) = 0;
        void virtual OnServoResponse(ServoResponse* message) = 0;
    public:
        #ifdef ARDUINO_BOARD
            Controller(uint8_t rx, uint8_t tx):Comms(rx, tx){}
        #else
            Controller():Comms(){}
        #endif
        void virtual WaitForDrone() = 0;
};
#endif
