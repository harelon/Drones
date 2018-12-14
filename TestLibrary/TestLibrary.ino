#include <SoftwareSerial.h>
#include <HDC1080JS.h>
#include <SparkFun_APDS9960.h>
#include <SendToScreen.h>
Drone drone(6,7);
void setup() {
  // put your setup code here, to run once:
drone.SetUpColorSensor().SetUpHeightSensor().SetUpTempSensor();
}

void loop() {
  // put your main code here, to run repeatedly:

}
