#include <Drone.h>
Drone::Drone(uint8_t rx,uint8_t tx):Comms(rx,tx)
{

}

Drone* Drone::SetUpTempSensor()
{
    _TempSensor.config();
    return this;
}

void Drone::SendTemperature()
{
    TemperatureResponse response;

    response.header.length=sizeof(TemperatureResponse);
    response.header.type=RESPONSE_FOR_TEMPERATURE;
    
    _TempSensor.readTempHumid();
    response.temperature=_TempSensor.getTemp();

    SendMessage(&response.header);
}

Drone* Drone::SetUpColorSensor()
{
    _LightSensor=SparkFun_APDS9960();
    _LightSensor.init();
    _LightSensor.enableLightSensor(false);
    return this;
}

void Drone::SendColor()
{
    ColorResponse response;

    response.header.length=sizeof(ColorResponse);
    response.header.type=RESPONSE_FOR_COLOR;
    if(!_LightSensor.readAmbientLight(ambient_light) ||
       !_LightSensor.readRedLight(red_light) ||
       !_LightSensor.readGreenLight(green_light) ||
       !_LightSensor.readBlueLight(blue_light)){
        return;
    }

    response.color.r = (int)((float)(red_light & 0xFF00) * transmitionRate) >> 8;
    response.color.g = (int)((float)(green_light & 0xFF00) * transmitionRate) >> 8;
    response.color.b = (int)((float)(blue_light & 0xFF00) * transmitionRate) >> 8;

    SendMessage(&response.header);
}

Drone* Drone::SetUpHeightSensor()
{
    return this;
}

void Drone::SendHeight()
{
    HeightResponse response;

    response.header.length=sizeof(HeightResponse);
    response.header.type=RESPONSE_FOR_HEIGHT;
    
   //response.height=;

    SendMessage(&response.header);
}