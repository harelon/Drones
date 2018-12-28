#include "Drone.h"
<<<<<<< HEAD
Drone drone(12, 11);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor()->SetUpHeightSensor(9,10);
=======
Drone drone(6, 9);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor();
  Serial.begin(9600);
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
}
void loop() {
  drone.PollMessage();  
}
