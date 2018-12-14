#include <Drone.h>
Drone drone(6,7);
void setup() {
  // put your setup code here, to run once:
drone.SetUpColorSensor().SetUpHeightSensor().SetUpTempSensor();
}

void loop() {
  // put your main code here, to run repeatedly:

}
