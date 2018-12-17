#include "Controller.h"
Controller Controller(6,7);
//Controller* ControllerRef=&Controller;
MessageHeader* message;
void setup() {
  //ControllerRef->SetUpTempSensor()->SetUpColorSensor();
}

void loop() {
  Controller.RecieveMessage(message);

}
