#include <SoftwareSerial.h>
#include "spiUnit.h"
#include "TFT9341.h"
#include "touch.h"
#include <SPI.h>

SoftwareSerial mySerial(5, 6);

void setup() {
  // init serial communication and screen
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
  // the distance is sent in 2 bytes and we don't want to read only one
  // so we wait until there are 2 bytes waiting to be sent
  if (mySerial.available() >= 2)
  {
    // read the most significant byte that was sent into an int and shift it 8 positions to the left
    // so it would be the most signifcant byte in the int
    // also read the least significant byte into the position of the least significant byte in the int
    int x = (mySerial.read() << 8) | (mySerial.read());    
    lcd.print(x);
    delay(500);
    lcd.fillRoundRect(20, 20, 70, 40,0,BLACK);
    lcd.setColor(CYAN);
    lcd.gotoxy(25, 30);
  }
}
