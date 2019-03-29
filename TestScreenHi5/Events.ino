void ScreenLib::OnRawColorResponse(RawColorResponse* message)
{
  PrintStatus(&lcd, "RAW COLOR RESPONDED");
  PrintResult(&lcd);
  byte r = message->color.r;
  byte g = message->color.g;
  byte b = message->color.b;
  lcd.print("r=");
  lcd.print(r);
  lcd.print(" g=");
  lcd.print(g);
  lcd.print(" b=");
  lcd.print(b);
}
void ScreenLib::OnColorResponse(ColorResponse* message)
{
  PrintStatus(&lcd, "COLOR RESPONDED");
  PrintResult(&lcd);
  MainColors c = message->color;
  switch (c)
  {
    case MAIN_NONE:
      lcd.print("NONE");
      break;
    case MAIN_RED:
      lcd.print("RED");
      break;
    case MAIN_GREEN:
      lcd.print("GREEN");
      break;
    case MAIN_BLUE:
      lcd.print("BLUE");
      break;
    case MAIN_WHITE:
      lcd.print("WHITE");
      break;
    default:
      lcd.print("BLACK");
      break;
  }
}
void ScreenLib::OnHeightResponse(HeightResponse* message)
{
  PrintStatus(&lcd, "HEIGHT RESPONDED");
  PrintResult(&lcd);
  lcd.print(message->height);
}
void ScreenLib::OnGyroResponse(GyroResponse* message)
{
  PrintStatus(&lcd, "GYRO RESPONDED");
  String s = "p=" + String((int)message->angularOrientation.pitch) + " r=" + String((int)message->angularOrientation.roll) + " y=" + String((int)message->angularOrientation.yaw);
  PrintResult(&lcd);
}
void ScreenLib::OnServoResponse(ServoResponse* message)
{
  PrintStatus(&lcd, "SERVO RESPONDED");
}
