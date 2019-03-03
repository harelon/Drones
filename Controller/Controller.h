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

        void virtual OnTemperatureResponse(TemperatureResponse* message) = 0;
        void virtual OnRawColorResponse(RawColorResponse* message) = 0;
        void virtual OnColorResponse(ColorResponse* message) = 0;
        void virtual OnHeightResponse(HeightResponse* message) = 0;
        void virtual OnBuzzResponse(BuzzResponse* message) = 0;
    public:
        Controller(uint8_t rx, uint8_t tx);
};
#endif
