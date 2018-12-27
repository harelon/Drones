#ifndef Drone_H
#define Drone_H

#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>

#include <Comms.h>

class Drone: public Comms
{   
    private:
        HDC1080JS _TempSensor;
        //HeightSensor;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 65536.0 / 37889.0;        
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
    protected:
        void virtual OnColorRequest();
        void virtual OnTemperatureRequest();
        void virtual OnHeightRequest();
        void SendTemperature();
        void SendColor();
        void SendHeight();        
    public:
        Drone(uint8_t rx,uint8_t tx);
        Drone* SetUpTempSensor();
        Drone* SetUpColorSensor();
        Drone* SetUpHeightSensor();
};
#endif
