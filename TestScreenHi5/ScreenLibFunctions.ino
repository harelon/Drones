void ScreenLib::MainScreen()
{
  lcd.fillScreen(ILI9341_BLACK);
  lcd.setTextSize(2);
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
    buttons[i].drawButton();
  }
  lcd.drawRect(0, 225, 240, 45, ILI9341_YELLOW);
  lcd.drawRect(0, 271, 240, 45, ILI9341_GREEN);
  PrintStatus(&lcd, "STATUS PANEL");
  PrintResult(&lcd, "RESULT PANEL");
}

void ScreenLib::PollScreen()
{

  if (lcdtouch.dataAvailable())
  {
    lcdtouch.read();
    x = lcdtouch.getX();
    y = lcdtouch.getY();

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
      if (buttons[i].contains(x, y))
      {
        _currentButtonId = i;
        break;
      }
    }
  }
  if (_currentButtonId == _lastButtonId)
  {
    return;
  }
  switch (_currentButtonId)
  {
    case BUTTON_RAW_COLOR: RawColorReq(); break;
    case BUTTON_HEIGHT: HeightReq(); break;
    case BUTTON_COLOR: ColorReq(); break;
    case BUTTON_GYRO: GyroReq(); break;
    case BUTTON_SERVO_RED: ServoReq(SERVO_RED); break;
    case BUTTON_SERVO_GREEN: ServoReq(SERVO_GREEN); break;
    case BUTTON_SERVO_BLUE: ServoReq(SERVO_BLUE); break;
    default: break;
  }
  _lastButtonId = _currentButtonId;
}
