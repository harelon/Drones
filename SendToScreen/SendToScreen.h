#ifndef Send_To_Screen_H
#define Send_To_Screen_H

// #include <Arduino.h>

enum MessageTypes
{
    REQUEST_FOR_TEMPRATURE = 1,
    RESPONSE_FOR_TEMPRATURE = 2,
    REQUEST_FOR_COLOR=3,
    RESPONSE_FOR_COLOR=4,
    REQUEST_FOR_HEIGHT=5,
    RESPONSE_FOR_HEIGHT=6,  
};

enum requestOptions {
  nothing,
  height,
  temprature,
  color,
  buzzer,
  stopBuzzer
};

enum colorResult {
  red,
  green,
  blue,
  white
};
typedef struct {
  byte r;
  byte g;
  byte b;
} rgbColor;

typedef struct{
    byte length;
    byte type;    
}MessageHeader;

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