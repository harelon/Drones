#ifndef Comms_H
#define Comms_H

#include <BasicSerial.h>
#include <Utils.h>

#pragma pack(push, 1)

typedef struct{
    byte length;
    byte type;
}MessageHeader;

class Comms
{
    private:
         byte msgBuffer[20];
         BasicSerial _serial;
         byte *pRecieve = nullptr;
         byte *endRecieve = pRecieve - 1;
         bool gotLength = false;
         MessageHeader *pMainMessage = (MessageHeader *)msgBuffer;
    protected:
        void SendMessage(MessageHeader* message);
        bool ReceiveMessage(MessageHeader* message);
        void virtual DispatchMessage(MessageHeader* message) = 0;
    public:
         #ifdef ARDUINO_BOARD
            Comms(uint8_t rx, uint8_t tx):_serial(rx, tx){}
         #else
            Comms():_serial(){}
         #endif
        void PollMessage();
};

enum MessageTypes
{
    DRONE_CONNECTED = 0,
    REQUEST_FOR_TEMPERATURE = 1,
    RESPONSE_FOR_TEMPERATURE = 2,
    REQUEST_FOR_COLOR = 3,
    RESPONSE_FOR_COLOR = 4,
    REQUEST_RAW_COLOR = 5,
    RESPONSE_RAW_COLOR = 6,
    REQUEST_FOR_HEIGHT = 7,
    RESPONSE_FOR_HEIGHT = 8,
    REQUEST_BUZZ_ON = 9,
    RESPONSE_BUZZ_ON = 10,
    REQUEST_BUZZ_OFF = 11,
    RESPONSE_BUZZ_OFF = 12,
    REQUEST_ANGULAR_ORIENTATION = 13,
    RESPONSE_ANGULAR_ORIENTATION = 14,
    REQUEST_SERVO_DROP = 15,
    RESPONSE_SERVO_DROP = 16,
};

typedef struct {
   MessageHeader header;
} DroneConnected;



/*start of requests*/

typedef struct{
   MessageHeader header;
}TemperatureRequest;

typedef struct{
   MessageHeader header;
}ColorRequest;

typedef struct{
   MessageHeader header;
}RawColorRequest;

typedef struct{
   MessageHeader header;
}HeightRequest;

typedef struct{
   MessageHeader header;
}BuzzRequest;

typedef struct{
   MessageHeader header;
}GyroRequest;

typedef struct{
   MessageHeader header;
   byte servoColor;
}ServoRequest;

/*end of requests*/
/*start of responses*/

typedef struct{
   MessageHeader header;
   float temperature;
}TemperatureResponse;

typedef struct{
   MessageHeader header;
   uint32_t color;
}ColorResponse;

typedef struct{
   MessageHeader header;
   rgbColor color;
}RawColorResponse;

typedef struct{
   MessageHeader header;
   uint16_t height;
}HeightResponse;

typedef struct{
   MessageHeader header;
}BuzzResponse;

typedef struct{
   MessageHeader header;
   AngularOrientation angularOrientation;
}GyroResponse;

typedef struct{
   MessageHeader header;
   byte state;
}ServoResponse;

#pragma pack(pop)
/*end of responses*/

#endif
