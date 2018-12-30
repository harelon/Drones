#include <Ultrasonic.h>
#define redPort1 1
#define redPort2 2
#define greenPort1 3
#define greenPort2 4
#define bluePort 5
Ultrasonic sensor(9, 10);
#define meters 100

void setup() 
{
  pinMode(redPort1, OUTPUT);
  pinMode(redPort2, OUTPUT);
  pinMode(greenPort1, OUTPUT);
  pinMode(greenPort2, OUTPUT);
  pinMode(bluePort, OUTPUT);
}

void loop() 
{
  int distance = sensor.read();
  if (distance > 3 * meters)
  {
    analogWrite(redPort1, 255);
    analogWrite(redPort2, 255);
    analogWrite(greenPort1, 165);
    analogWrite(greenPort2, 165);
    analogWrite(bluePort, 0);
  }
  else if (distance > 2 * meters)
  {
    analogWrite(redPort1, 0);
    analogWrite(redPort2, 0);
    analogWrite(greenPort1, 0);
    analogWrite(greenPort2, 0);
    analogWrite(bluePort, 255);
  }
  else if (distance > 1 * meters)
  {
    analogWrite(redPort1, 0);
    analogWrite(redPort2, 0);
    analogWrite(greenPort1, 255);
    analogWrite(greenPort2, 0);
    analogWrite(bluePort, 0);
  }
  else
  {
    analogWrite(redPort1, 255);
    analogWrite(redPort2, 0);
    analogWrite(greenPort1, 0);
    analogWrite(greenPort2, 0);
    analogWrite(bluePort, 0);
  }
}
