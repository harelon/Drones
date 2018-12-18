#include "Drone.h"
Drone drone(6,7);
Drone* droneRef=&drone;
MessageHeader* message;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor();
}

void loop() {
  if(drone.RecieveMessage(message))
  {
    if(message->type==REQUEST_FOR_TEMPERATURE)
    {
      drone.SendTemperature();
    }
    if(message->type==REQUEST_FOR_COLOR)
    {
      drone.SendColor();
    }
    if(message->type==REQUEST_FOR_HEIGHT)
    {
      drone.SendHeight();
    }
  }
}
