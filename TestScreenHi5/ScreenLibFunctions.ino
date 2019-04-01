ScreenLib::ScreenLib() : lcd(TFT_CS, TFT_DC), lcdtouch(T_IRQ, T_SS), Controller() {
  lcd.begin(5000000);
  lcdtouch.begin();
  lcd.setRotation(2);
  lcdtouch.setRotation(2);
  buttons[BUTTON_COLOR].initButton(&lcd, 60, 30, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "COLOR", 2);
  buttons[BUTTON_RAW_COLOR].initButton(&lcd, 180, 30, 120, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "RAW COLOR", 2);
  buttons[BUTTON_HEIGHT].initButton(&lcd, 60, 85, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "HEIGHT", 2);
  buttons[BUTTON_GYRO].initButton(&lcd, 180, 85, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "GYRO", 2);
  buttons[BUTTON_SERVO_RED].initButton(&lcd, 60, 140, 100, 50, ILI9341_BLACK, ILI9341_RED, ILI9341_CYAN, "SERVO", 2);
  buttons[BUTTON_SERVO_GREEN].initButton(&lcd, 180, 140, 100, 50, ILI9341_BLACK, ILI9341_GREEN, ILI9341_MAGENTA, "SERVO", 2);
  buttons[BUTTON_SERVO_BLUE].initButton(&lcd, 60, 195, 100, 50, ILI9341_BLACK, ILI9341_BLUE, ILI9341_YELLOW, "SERVO", 2);
}

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
  long currentTime = millis();
  if (currentTime - _lastButtonTime < 500)
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
  _currentButtonId = -1;
  _lastButtonTime = currentTime;
}
