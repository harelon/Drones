#include <SendToScreen.h>

Comms::Comms(SoftwareSerial* serial)
{
    _serial=serial;
    _serial->begin(9600);
}

Controller::Controller(SoftwareSerial* serial):Comms(serial)
{

}

Drone::Drone(SoftwareSerial* serial):Comms(serial)
{

}

void Comms::SendMessage(MessageHeader* message)
{   
    byte* p=(byte*)message;
    byte* end=p+message->length;
    while(p<end)
    {
        _serial->write(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    byte size=_serial->read();
    byte* p=(byte*)message;
    message->length=size;
    byte* end=p+size;
    p++;
    while(p<end)
    {
        *p=_serial->read();
        p++;
    }
}

void Controller::RequestForTemperature()
{
    TemperatureRequest request;

    request.header.length=sizeof(TemperatureRequest);
    request.header.type=REQUEST_FOR_TEMPERATURE;

    SendMessage(&request.header);
}

void Drone::SetUpTempSensor()
{
    _TempSensor.config();
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

void Controller::RequestForColor()
{
    ColorRequest request;

    request.header.length=sizeof(ColorRequest);
    request.header.type=REQUEST_FOR_COLOR;

    SendMessage(&request.header);
}

void Drone::SetUpColorSensor()
{
    _LightSensor=SparkFun_APDS9960();
    _LightSensor.init();
    _LightSensor.enableLightSensor(false) ;
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

void Controller::RequestForHeight()
{
    HeightRequest request;

    request.header.length=sizeof(HeightRequest);
    request.header.type=REQUEST_FOR_HEIGHT;

    SendMessage(&request.header);
}

void Drone::SetUpHeightSensor()
{

}

void Drone::SendHeight()
{
    HeightResponse response;

    response.header.length=sizeof(HeightResponse);
    response.header.type=RESPONSE_FOR_HEIGHT;
    
   //response.height=;

    SendMessage(&response.header);
}