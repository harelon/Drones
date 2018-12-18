#include "Controller.h"
Controller Controller(6,7);
MessageHeader* message;
void setup() {
}

void loop() {
  if(Controller.RecieveMessage(message))
  {
    if(message->type==RESPONSE_FOR_TEMPERATURE)
    {
      show((TemperatureResponse*)message->temp);
    }
    if(message->type==RESPONSE_FOR_COLOR)
    {
      show((ColorResponse*)message->rgbColor.r);// can be go or b
    }
    if(message->type==RESPONSE_FOR_HEIGHT)
    {
      show((HeightResponse*)message->height);
    }
  }
}
