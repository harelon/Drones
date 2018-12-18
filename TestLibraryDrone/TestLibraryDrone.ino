#include "Drone.h"
Drone drone(6,7);
Drone* droneRef=&drone;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor();
}

void loop() {
  drone.PollMessage();
}
