void HeightFormat(char* result_message, uint16_t num)
{
  strcpy(result_message, "HEIGHT=");
  int len = strlen(result_message);
  result_message[len++] = (num / 100) + '0';
  result_message[len++] = ((num / 10) % 10) + '0';
  result_message[len++] = (num % 10) + '0';
  result_message[len++] = 0;
}
void ColorFormat(char* result_message, uint32_t color)
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
    case MAIN_INTERMEDIATE:
      strcpy(result_message, "CAN'T DETERMINE");
      break;
  }
}
void RawColorFormat(char* result_message, rgbColor color)
{
  result_message[0] = 'R';
  result_message[1] = '=';
  result_message[2] = (color.r / 100) + '0';
  result_message[3] = ((color.r / 10) % 10) + '0';
  result_message[4] = (color.r % 10) + '0';
  result_message[5] = ' ';
  result_message[6] = 'G';
  result_message[7] = '=';
  result_message[8] = (color.g / 100) + '0';
  result_message[9] = ((color.g / 10) % 10) + '0';
  result_message[10] = (color.g % 10) + '0';
  result_message[11] = ' ';
  result_message[12] = 'B';
  result_message[13] = '=';
  result_message[14] = (color.b / 100) + '0';
  result_message[15] = ((color.b / 10) % 10) + '0';
  result_message[16] = (color.b % 10) + '0';
  result_message[17] = 0;

}
void GyroFormat(char* result_message, AngularOrientation angularOrientation)
{
  int16_t pitch =  angularOrientation.pitch;
  int16_t roll =  angularOrientation.roll;
  int16_t yaw = angularOrientation.yaw;
  result_message[0] = 'P';
  result_message[1] = '=';
  if (pitch < 0)
  {
    result_message[2] = '-';
    result_message[3] = ((-pitch / 10) % 10) + '0';
    result_message[4] = (-pitch % 10) + '0';
  }
  else if (pitch > 0)
  {
    result_message[2] = '+';
    result_message[3] = ((pitch / 10) % 10) + '0';
    result_message[4] = (pitch % 10) + '0';
  }
  else
  {
    result_message[2] = '0';
    result_message[3] = '0';
    result_message[4] = '0';
  }

  result_message[5] = ' ';
  result_message[6] = 'R';
  result_message[7] = '=';
  if (roll < 0)
  {
    result_message[8] = '-';
    result_message[9] = ((-roll / 10) % 10) + '0';
    result_message[10] = (-roll % 10) + '0';
  }
  else if (roll > 0)
  {
    result_message[8] = '+';
    result_message[9] = ((roll / 10) % 10) + '0';
    result_message[10] = (roll % 10) + '0';
  }
  else
  {
    result_message[8] = '0';
    result_message[9] = '0';
    result_message[10] = '0';
  }

  result_message[11] = ' ';
  result_message[12] = 'Y';
  result_message[13] = '=';
  if (yaw < 0)
  {
    result_message[14] = '-';
    result_message[15] = ((-yaw / 10) % 10) + '0';
    result_message[16] = (-yaw % 10) + '0';
  }
  else if (yaw > 0)
  {
    result_message[14] = '+';
    result_message[15] = ((yaw / 10) % 10) + '0';
    result_message[16] = (yaw % 10) + '0';
  }
  else
  {
    result_message[14] = '0';
    result_message[15] = '0';
    result_message[16] = '0';
  }

  result_message[17] = 0;
}
void ServoFormat(char* result_message, BallStates state)
{
  switch (state)
  {
    case NOT_LOADED:
      strcpy(result_message, "NOT LOADED");
      break;
    case NEED_TO_LOAD:
      strcpy(result_message, "NEED TO LOAD");
      break;
    case LOADED:
      strcpy(result_message, "LOADED");
      break;
    case DROPPED:
      strcpy(result_message, "DROPPED");
      break;
  }
}
