#ifdef UseController

#ifndef Controller_H
#define Controller_H

#include <Comms.h>

class Controller:Comms
{
    public:
        Controller(uint8_t rx,uint8_t tx);
        void RequestForTemperature();
        void RequestForColor();
        void RequestForHeight();
};

#endif

#endif