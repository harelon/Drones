#include "Drone.h"
Drone drone(6,7);
Drone* droneRef=&drone;
MessageHeader* message;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor();
}

void loop() {
  droneRef->SendTemperature();

}
