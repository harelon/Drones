void PrintStatus(Adafruit_ILI9341* lcd, char* s)
{
  lcd->fillRect(1, 226, 238, 43, ILI9341_BLACK);
  lcd->setCursor(12, 237);
  lcd->setTextColor(ILI9341_YELLOW);
  lcd->print(s);
}

void PrintResult(Adafruit_ILI9341* lcd)
{
  lcd->fillRect(1, 272, 238, 43, ILI9341_BLACK);
  lcd->setCursor(12, 286);
  lcd->setTextColor(ILI9341_GREEN);
}
