#include <ServoBall.h>
#define ServoNumbers 3
ServoBall balls[ServoNumbers];
void setup() {
  // put your setup code here, to run once:
  SetUpServo(A3, SERVO_BLUE);
  SetUpServo(A4, SERVO_GREEN);
  SetUpServo(A5, SERVO_RED);
  Serial.begin(9600);
  for(int i = 0; i < ServoNumbers; i++)
  {
    Serial.println(i);
    Serial.println("ball i state before lock = " + String(balls[i].GetState()));
    balls[i].Lock();
    Serial.println("ball i state after lock = " + String(balls[i].GetState()));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    char readC = Serial.read();
    if('0' <= readC && readC <= '2')
    {
      char ballNumber = readC - '0';
      Serial.println("ball i state before drop = " + String(balls[ballNumber].GetState()));
      Serial.println("read number = " + String(readC));
      Serial.println("current ball state = " + String(DropBall(ballNumber)));
    }
  }
}
void SetUpServo(byte pin, ServoColors color, BallStates state)
{
    balls[color].Init(pin, color, state);
}

void SetUpServo(byte pin, ServoColors color)
{
   SetUpServo(pin, color, NEED_TO_LOAD);
}

BallStates DropBall(ServoColors color)
{
    return balls[color].Drop();
}
