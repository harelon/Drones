#include "Drone.h"
Drone drone(12, 11);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpHeightSensor(8);
}
void loop() {
  drone.PollMessage();  
}
