#include <SoftwareSerial.h>
#include "spiUnit.h"
#include "TFT9341.h"
#include "touch.h"
#include <SPI.h>

SoftwareSerial mySerial(5, 6);

void setup() {
  mySerial.begin(9600);  
  lcd.begin();
  lcdtouch.begin();
  lcdtouch.InitTypeTouch(2);//0,1,2
  lcd.setRotation(1);//0,1,2,3
  lcd.clrscr(BLACK);
  lcd.setColor(CYAN, BLACK);
  lcd.setFont(3);
  lcd.gotoxy(25, 30);
}

void loop() {
  if (mySerial.available() >= 2)
  {
    int x = (mySerial.read() << 8) | (mySerial.read());    
    lcd.print(x);
    delay(500);
    lcd.fillRoundRect(20, 20, 70, 40,0,BLACK);
    lcd.setColor(CYAN);
    lcd.gotoxy(25, 30);
  }
}
