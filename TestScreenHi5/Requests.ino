void ScreenLib::RawColorReq()
{
  PrintStatus(&lcd, "RAW COLOR REQUESTED");
  RequestRawColor();
  PrintStatus(&lcd, "WAITING FOR RAW\n COLOR");
}

void ScreenLib::ColorReq()
{
  PrintStatus(&lcd, "COLOR REQUESTED");
  RequestForColor();
  PrintStatus(&lcd, "WAITING FOR COLOR");
}

void ScreenLib::HeightReq()
{
  PrintStatus(&lcd, "HEIGHT REQUESTED");
  RequestForHeight();
  PrintStatus(&lcd, "WAITING FOR HEIGHT");
}

void ScreenLib::GyroReq()
{
  PrintStatus(&lcd, "GYRO REQUESTED");
  RequestForGyro();
  PrintStatus(&lcd, "WAITING FOR GYRO");
}

void ScreenLib::ServoReq(ServoColors color)
{
  PrintStatus(&lcd, "SERVO REQUESTED");
  RequestForServoDrop(color);
  PrintStatus(&lcd, "WAITING FOR SERVO");
}
