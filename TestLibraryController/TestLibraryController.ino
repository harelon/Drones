#include "ScreenCustom.h"
ScreenCustom screen(5 ,3);
void setup() {
  //Serial.begin(9600);
}

void loop() {  
  screen.PollMessage();
  screen.PollScreen();
}
