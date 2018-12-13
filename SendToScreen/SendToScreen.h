#ifndef Send_To_Screen_H
#define Send_To_Screen_H
#include <Arduino.h>
#include <SparkFun_APDS9960.h>
#include <HDC1080JS.h>
#include <SoftwareSerial.h>

typedef struct{
    byte length;
    byte type;    
}MessageHeader;

class Comms
{
    private:
        SoftwareSerial* _serial;
    protected:
        void SendMessage(MessageHeader* message);
        bool ReceiveMessage(MessageHeader* message);

    public:
        Comms(SoftwareSerial* serial);
};
class Controller:Comms
{
    public:
        Controller(SoftwareSerial* serial);
        void RequestForTemperature();
        void RequestForColor();
        void RequestForHeight();
};
class Drone:Comms
{   private:
        HDC1080JS _TempSensor;
        //HeightSensor;
        SparkFun_APDS9960 _LightSensor;
        const float transmitionRate = 65536.0 / 37889.0;        
        uint16_t ambient_light = 0;
        uint16_t red_light = 0;
        uint16_t green_light = 0;
        uint16_t blue_light = 0;
    public:
        Drone(SoftwareSerial* serial);
        void SetUpTempSensor();
        void SendTemperature();
        void SetUpColorSensor();
        void SendColor();
        void SetUpHeightSensor();
        void SendHeight();
};

enum MessageTypes
{
    REQUEST_FOR_TEMPERATURE = 1,
    RESPONSE_FOR_TEMPERATURE = 2,
    REQUEST_FOR_COLOR=3,
    RESPONSE_FOR_COLOR=4,
    REQUEST_FOR_HEIGHT=5,
    RESPONSE_FOR_HEIGHT=6,  
};

typedef struct {
  byte r;
  byte g;
  byte b;
} rgbColor;

typedef struct{
   MessageHeader header; 
}TemperatureRequest;

typedef struct{
   MessageHeader header; 
}ColorRequest;

typedef struct{
   MessageHeader header; 
}HeightRequest;

typedef struct{
   MessageHeader header;    
   float temperature;
}TemperatureResponse;

typedef struct{
   MessageHeader header;    
   rgbColor color;
}ColorResponse;
typedef struct{
   MessageHeader header;    
   int height;
}HeightResponse;

#endif