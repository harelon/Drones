#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
class Comms
{
    private:
        SoftwareSerial _serial;
    protected:
        void SendMessage(MessageHeader* message);
        bool ReceiveMessage(MessageHeader* message);

    public:
        Comms(int rx,int tx);
}
class Controller:Comms
{
    public:
        Controller(int rx, int tx);
        void RequestForTemprature();
        void RequestForLight();
        void RequestForHeight();
}
class Drone:Comms
{   private:
        HDC1080JS _TempSensor;
        //HeightSensor;
        SparkFun_APDS9960 _LightSensor;
        const transmitionRate = 65536.0 / 37889.0;        
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
    public:
        Drone(int rx, int tx);
        void SetUpTempSensor();
        void SendTemprature();
        void SetUpColorSensor();
        void SendColor();
        void SetUpHeight();
        void SendHeight();
}

Comms::Comms(int rx, int tx)
{
    _serial=SoftwareSerial(rx, tx);
}

Controller::Controller(int rx, int tx):Comms(rx, tx)
{

}

Drone::Drone(int rx, int tx):Comms(rx, tx)
{

}

void Comms::SendMessage(MessageHeader* message)
{   
    byte* p=(byte*)message;
    byte* end=p+message->length;
    while(p<end)
    {
        _serial.write(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    byte size=_serial.read();
    byte* p=(byte*)message;
    message->length=size;
    byte* end=p+size;
    p++;
    while(p<end)
    {
        *p=_serial.read();
        p++;
    }
}

void Controller::RequestForTemprature()
{
    TempratureRequest request;

    request.length=sizeof(TempratureRequest);
    request.type=REQUEST_FOR_TEMPRATURE;

    SendMessage(&request);
}

void Drone::SetUpTempSensor()
{
    TempSensor.config();
}

void Drone::SendTemprature()
{
    TemperatureResponse response;

    request.length=sizeof(TemperatureResponse);
    request.type=RESPONSE_FOR_TEMPRATURE;
    
    _TempSensor.readTempHumid();
    response.temperature=_TempSensor.getTemp();

    SendMessage(&response);
}

void Controller::RequestForColor()
{
    ColorRequest request;

    request.length=sizeof(ColorRequest);
    request.type=REQUEST_FOR_COLOR;

    SendMessage(&request);
}

void Drone::SetUpLightSensor()
{
    _LightSensor=SparkFun_APDS9960();
    _LightSensor.init();
    _LightSensor.enableLightSensor(false) ;
}

void Drone::ResponseForColor()
{
    ColorResponse response;

    response.length=sizeof(ColorResponse);
    response.type=RESPONSE_FOR_LIGHT;
    if(!apds.readAmbientLight(ambient_light) ||
       !apds.readRedLight(red_light) ||
       !apds.readGreenLight(green_light) ||
       !apds.readBlueLight(blue_light)){
        return;
    }

    response.rgbColor.r = (int)((float)(red_light & 0xFF00) * transmitionRate) >> 8;
    response.rgbColor.g = (int)((float)(green_light & 0xFF00) * transmitionRate) >> 8;
    response.rgbColor.b = (int)((float)(blue_light & 0xFF00) * transmitionRate) >> 8;

    SendMessage(&response);
}

void Controller::RequestForHeight()
{
    HeightRequest request;

    request.length=sizeof(HeightRequest);
    request.type=REQUEST_FOR_HEIGHT;

    SendMessage(&request);
}

void Drone::SetUpHeightSensor()
{

}

void Drone::SendHeight()
{
    HeightResponse response;

    request.length=sizeof(HeightResponse);
    request.type=RESPONSE_FOR_HEIGHT;
    
   //response.height=;

    SendMessage(&response);
}