#define UseDrone
#include <Drone.h>
Drone drone(6, 7);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpColorSensor()->SetUpHeightSensor()->SetUpTempSensor();
}

void loop() {
  // put your main code here, to run repeatedly:

}
