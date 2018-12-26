#ifndef Controller_H
#define Controller_H

#include "Comms.h"

class Controller : public Comms
{
    protected:
        void virtual DispatchMessage(MessageHeader* message);
        void RequestForTemperature();
        void RequestForColor();
        void RequestForHeight();
        void RequestForBuzzOn();
        void RequestForBuzzOff();

        bool ReceiveMessage(MessageHeader* message);        

        void virtual OnTemperatureResponse(TemperatureResponse* message)=0;
        void virtual OnColorResponse(ColorResponse* message)=0;
        void virtual OnHeightResponse(HeightResponse* message)=0;
        void virtual OnBuzzResponse(BuzzResponse* message)=0;

    public:
        Controller(uint8_t rx, uint8_t tx);        

};
#endif
