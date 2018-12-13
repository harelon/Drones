#include <SoftwareSerial.h>
#include <HDC1080JS.h>
#include <SparkFun_APDS9960.h>
#include <SendToScreen.h>
SoftwareSerial mySerial(6,7);
Drone drone(&mySerial);
void setup() {
  // put your setup code here, to run once:
drone.SetUpColorSensor();
drone.SetUpHeightSensor();
drone.SetUpTempSensor();
}

void loop() {
  // put your main code here, to run repeatedly:

}
