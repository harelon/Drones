void ScreenLib::OnRawColorResponse(RawColorResponse* message)
{
  PrintStatus(&lcd, "RAW COLOR RESPONDED");
  //  PrintResult(&lcd);
  byte r = message->color.r;
  byte g = message->color.g;
  byte b = message->color.b;
  lcd.print("R=");
  lcd.print(r);
  lcd.print(" G=");
  lcd.print(g);
  lcd.print(" B=");
  lcd.print(b);
}
void ScreenLib::OnColorResponse(ColorResponse* message)
{
  PrintStatus(&lcd, "COLOR RESPONDED");
  ColorFormat(result_message, message->color);
  PrintResult(&lcd, result_message);
}
void ScreenLib::OnHeightResponse(HeightResponse* message)
{
  PrintStatus(&lcd, "HEIGHT RESPONDED");
  HeightFormat(result_message, message->height);
  PrintResult(&lcd, result_message);
}
void ScreenLib::OnGyroResponse(GyroResponse* message)
{
  PrintStatus(&lcd, "GYRO RESPONDED");
  //  String s = "p=" + String((int)message->angularOrientation.pitch) + " r=" + String((int)message->angularOrientation.roll) + " y=" + String((int)message->angularOrientation.yaw);
  //  PrintResult(&lcd);
}
void ScreenLib::OnServoResponse(ServoResponse* message)
{
  PrintStatus(&lcd, "SERVO RESPONDED");
}
