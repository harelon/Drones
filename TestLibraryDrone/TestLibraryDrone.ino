#include "Drone.h"
Drone drone(5, 4);
Drone* droneRef = &drone;
void setup() {
  Serial.begin(9600);
  droneRef->SetUpColorSensor()->SetUpHeightSensor(8)->SetUpGyro();
  droneRef->SetUpServo(9,SERVO_RED)->SetUpServo(10,SERVO_GREEN)->SetUpServo(11,SERVO_BLUE);
}
void loop() {
  drone._Gyro.startTime();
  drone.PollMessage();
  drone._Gyro.updateValues();
}
