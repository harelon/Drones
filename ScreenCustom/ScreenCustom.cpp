#include <ScreenCustom.h>

ScreenCustom::ScreenCustom(uint8_t rx,uint8_t tx):Controller(rx,tx)
{

}

void OnTemperatureResponse(TemperatureResponse* message)
{
    lcd.setColor(YELLOW, BLACK);
    lcd.gotoxy (25, 30);
    lcd.print(message->temperature);
}

void OnColorResponse(ColorResponse* message)
{
    lcd.setColor(YELLOW, BLACK);
    lcd.gotoxy (25, 30);
    lcd.print("red:");
    lcd.gotoxy (25, 110);
    lcd.print("green:");
    lcd.gotoxy (25, 150);
    lcd.print("blue:");
    lcd.gotoxy (110, 70);
    lcd.print(message->color.r);
    lcd.gotoxy (110, 110);
    lcd.print(message->color.g);
    lcd.gotoxy (110, 150);
    lcd.print(message->color.b);
}

void OnHeightResponse(HeightResponse* message)
{
    lcd.setColor(YELLOW, BLACK);
    lcd.gotoxy (25, 30);
    lcd.print(message->height);
}

void printGeneralScreen()
{
  lcd.clrscr(BLACK);
  lcd.fillRoundRect (160, 270, 70, 40, 5, YELLOW);
  lcd.setColor(BLACK, YELLOW);
  lcd.setFont(2);
  lcd.gotoxy(170, 280);
  lcd.print("Main");
  lcd.setFont(3);
}

void MainScreen()
{
    lcd.clrscr(BLACK);
    lcd.setFont(2);
    lcd.fillRoundRect(20, 20, 70, 40, 5, RED);
    lcd.fillRoundRect(20, 80, 70, 40, 5, RED);
    lcd.fillRoundRect(20, 140, 80, 40, 5, RED);
    lcd.fillRoundRect(20, 200, 80, 40, 5, RED);
    lcd.fillRoundRect(20, 260, 105, 40, 5, RED);
    lcd.setColor(WHITE, RED);
    lcd.gotoxy(25, 30);
    lcd.print("COLOR");
    lcd.gotoxy(25, 90);
    lcd.print("TEMP");
    lcd.gotoxy(25, 150);
    lcd.print("HEIGTH");
    lcd.gotoxy(25, 210);
    lcd.print("BUZZER");
    lcd.gotoxy(25, 270);
    lcd.print("RF DEBUG");

    if (digitalRead(2) == 0)
    {
        lcdtouch.readxy();
        x = lcdtouch.readx();
        y = lcdtouch.ready();
        if ((x > 20) && (x < 90) && (y > 20) && (y < 60))
        {
          while (digitalRead(2) != 0 || !((x > 20) && (x < 90) && (y > 80) && (y < 120)))
          {
            printGeneralScreen();
            Controller.RequestForColor();
            delay(500);
          }
        }
        if ((x > 20) && (x < 90) && (y > 80) && (y < 120))
        {
          while (digitalRead(2) != 0 || !((x > 20) && (x < 90) && (y > 80) && (y < 120)))
          {
            printGeneralScreen();
            Controller.RequestForTemperature();
            delay(500);
          }
        }
        if ((x > 20) && (x < 90) && (y > 140) && (y < 180))
        {
            while (digitalRead(2) != 0 || !((x > 20) && (x < 90) && (y > 80) && (y < 120)))
            {
                printGeneralScreen();
                Controller.RequestForHeight();
                delay(500);
            }
        }
        if ((x > 20) && (x < 90) && (y > 200) && (y < 240))
        {
          /*buzzer screen*/
        }
        if ((x > 20) && (x < 90) && (y > 260) && (y < 300))
        {
          /*RF debug screen.no longer needed*/
        }
    }
}
