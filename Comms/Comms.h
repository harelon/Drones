#ifndef Comms_H
#define Comms_H

#include <Arduino.h>
#include <SoftwareSerial.h>

typedef struct{
    byte length;
    byte type;    
}MessageHeader;

class Comms
{
    private:
         SoftwareSerial _serial;         
         byte *pRecieve = nullptr;
         byte *endRecieve = pRecieve - 1;
         bool gotLength = false;
         byte msgBuffer[20];
         MessageHeader *pMainMessage;
    protected:
        void SendMessage(MessageHeader* message);
        bool ReceiveMessage(MessageHeader* message);
        void virtual DispatchMessage(MessageHeader* message) = 0;        
    public:
        Comms(uint8_t rx, uint8_t tx);
        void PollMessage();
};

enum MessageTypes
{
    REQUEST_FOR_TEMPERATURE = 1,
    RESPONSE_FOR_TEMPERATURE = 2,
    REQUEST_FOR_COLOR = 3,
    RESPONSE_FOR_COLOR = 4,
    REQUEST_FOR_HEIGHT = 5,
    RESPONSE_FOR_HEIGHT = 6,
    REQUEST_BUZZ_ON = 7,
    RESPONSE_BUZZ_ON = 8,
    REQUEST_BUZZ_OFF = 9,
    RESPONSE_BUZZ_OFF = 10,
};

typedef struct {
  uint16_t r;
  uint16_t g;
  uint16_t b;
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
}BuzzRequest;

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

typedef struct{
   MessageHeader header;
}BuzzResponse;

#endif
