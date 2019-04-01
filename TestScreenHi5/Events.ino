void ScreenLib::OnRawColorResponse(RawColorResponse* message)
{
  PrintStatus(&lcd, "RAW COLOR RESPONDED");
  RawColorFormat(result_message, message->color);
  PrintResult(&lcd, result_message);
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
  GyroFormat(result_message, message->angularOrientation);
  PrintResult(&lcd, result_message);
}
void ScreenLib::OnServoResponse(ServoResponse* message)
{
  PrintStatus(&lcd, "SERVO RESPONDED");
  ServoFormat(result_message, message->state);
  PrintResult(&lcd, result_message);
}
