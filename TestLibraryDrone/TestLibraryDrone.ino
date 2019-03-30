#include "Drone.h"
Drone drone(5, 4);
Drone* droneRef = &drone;
void setup() {
  Serial.begin(9600);
  droneRef->SetUpColorSensor()->SetUpHeightSensor(8);
}
void loop() {
  drone.PollMessage();  
}
