#ifndef Controller_H
#define Controller_H

#include "spiUnit.h"
#include "TFT9341.h"
#include "touch.h"
#include <SPI.h>

#include "Comms.h"

class Controller:Comms
{
    public:
        Controller(uint8_t rx,uint8_t tx);
        void RequestForTemperature();
        void RequestForColor();
        void RequestForHeight();
        bool ReceiveMessage(MessageHeader* message);
};

#endif