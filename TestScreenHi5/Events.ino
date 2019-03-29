void ScreenLib::OnRawColorResponse(RawColorResponse* message)
{
  String s = "r=" + String(message->color.r) + " g=" + String(message->color.g) + " b=" + String(message->color.b);
  PrintResult(&lcd, s.c_str());
  PrintStatus(&lcd, "RAW COLOR RESPONDED");
}
void ScreenLib::OnColorResponse(ColorResponse* message)
{
  char* res;
  switch (message->color)
  {
    case MAIN_NONE:
      res = "BLACK";
      break;
    case MAIN_RED:
      res = "RED";
      break;
    case MAIN_GREEN:
      res = "GREEN";
      break;
    case MAIN_BLUE:
      res = "BLUE";
      break;
    case MAIN_WHITE:
      res = "WHITE";
      break;
    default:
      res = "NO COLOR";
      break;
  }
  PrintResult(&lcd, res);
  PrintStatus(&lcd, "COLOR RESPONDED");
}
void ScreenLib::OnHeightResponse(HeightResponse* message)
{
  PrintResult(&lcd, message->height);
  PrintStatus(&lcd, "HEIGHT RESPONDED");
}
void ScreenLib::OnGyroResponse(GyroResponse* message)
{
  //TODO fix the line below;
  String s = "p=" + String(message->angularOrientation.pitch) + " r=" + String(message->angularOrientation.roll) + " y=" + String(message->angularOrientation.yaw);
  PrintResult(&lcd, s.c_str());
  PrintStatus(&lcd, "GYRO RESPONDED");
}
void ScreenLib::OnServoResponse(ServoResponse* message)
{
  PrintStatus(&lcd, "SERVO RESPONDED");
}
