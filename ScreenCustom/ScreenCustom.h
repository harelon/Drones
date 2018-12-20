#ifndef ScreenCustom_H
#define ScreenCustom_H

#include "spiUnit.h"
#include "TFT9341.h"
#include "touch.h"
#include <SPI.h>

#include "Controller.h"

class ScreenCustom:Controller
{
    protected:
        void override OnTemperatureResponse(TemperatureResponse* message);
        void override OnColorResponse(ColorResponse* message);
        void override OnHeightResponse(HeightResponse* message);
    public:
        ScreenCustom(uint8_t rx, uint8_t tx);
};

#endif
