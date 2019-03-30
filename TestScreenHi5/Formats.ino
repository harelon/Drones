void HeightFormat(char* result_message, uint16_t num)
{
  strcpy(result_message, "height=");
  int len = strlen(result_message);
  result_message[len++] = (num / 100) + '0';
  result_message[len++] = ((num / 10) % 10) + '0';
  result_message[len++] = (num % 10) + '0';
  result_message[len++] = 0;
}
void ColorFormat(char* result_message, MainColors color)
{
  switch (color)
  {
    case MAIN_RED:
      strcpy(result_message, "RED");
      break;
    case MAIN_GREEN:
      strcpy(result_message, "GREEN");
      break;
    case MAIN_BLUE:
      strcpy(result_message, "BLUE");
      break;
    case MAIN_WHITE:
      strcpy(result_message, "WHITE");
      break;
    case MAIN_NONE:
      strcpy(result_message, "NONE");
      break;
  }
}
void RawColorFormat(char* result_message, rgbColor color)
{

}
void GyroFormat(char* result_message, AngularOrientation angularOrientation)
{

}
void ServoFormat(char* result_message, BallStates state)
{

}
