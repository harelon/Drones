#include "Drone.h"
Drone drone(12, 11);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor()->SetUpHeightSensor(9,10);
}
void loop() {
  drone.PollMessage();  
}
