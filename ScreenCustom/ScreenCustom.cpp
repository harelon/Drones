#include <ScreenCustom.h>

ScreenCustom::ScreenCustom(uint8_t rx, uint8_t tx):Controller(rx, tx)
{
  lcd.begin();
  lcdtouch.begin();
  lcdtouch.InitTypeTouch(2);//0,1,2
  lcd.setRotation(1);//0,1,2,3
  lcd.setFont(2);

  _buttons[0].Init(BUTTON_RAW_COLOR, 20, 20, 70, 40, "Color", WHITE, RED);
  _buttons[1].Init(BUTTON_TEMP, 20, 80, 70, 40, "Temp", WHITE, RED);
  _buttons[2].Init(BUTTON_HEIGHT, 120, 20, 80, 40, "Height", WHITE, RED);
  _buttons[3].Init(BUTTON_BUZZ_ON, 120, 80, 90, 40, "Buzz on", WHITE, RED);
  _buttons[4].Init(BUTTON_BUZZ_OFF, 120, 140, 110, 40, "Buzz off", WHITE, RED);
  _statusPanel.Init(0, 200, 240, 60, "some text", GREEN, BLACK);
  _resultPanel.Init(0, 261, 240, 60, "some text", YELLOW, BLACK);

  MainScreen();
}

void ScreenCustom::OnTemperatureResponse(TemperatureResponse* message)
{
  _statusPanel.SetText("Temperature responded");
  _resultPanel.SetText(String(message->temperature));
}

void ScreenCustom::OnRawColorResponse(RawColorResponse* message)
{
  _statusPanel.SetText("Color responded");
  _resultPanel.SetText(String(message->color.r+', ' + message->color.g + ', ' + message->color.b));
}

void ScreenCustom::OnColorResponse(ColorResponse* message)
{
  
}

void ScreenCustom::OnHeightResponse(HeightResponse* message)
{
  _statusPanel.SetText("Height responded");
  _resultPanel.SetText(String(message->height));
}

void ScreenCustom::OnBuzzResponse(BuzzResponse* message)
{
  _statusPanel.SetText("Buzzer responded");
  _resultPanel.SetText(String(message->header.type));
}

void ScreenCustom::TemperatureReq()
{
  _statusPanel.SetText("Temperature pressed");
  RequestForTemperature();
  _statusPanel.SetText("Waiting for temperature");
}

void ScreenCustom::RawColorReq()
{
  _statusPanel.SetText("Color pressed");
  RequestRawColor();
  _statusPanel.SetText("Waiting for color");
}

void ScreenCustom::HeightReq()
{
  _statusPanel.SetText("Height pressed");
  RequestForHeight();
  _statusPanel.SetText("Waiting for height");
}

void ScreenCustom::BuzzOnReq()
{
  _statusPanel.SetText("Buzzer-on pressed");
  RequestForBuzzOn();
}

void ScreenCustom::BuzzOffReq()
{
  _statusPanel.SetText("Buzzer-off pressed");
  RequestForBuzzOff();
}

void ScreenCustom::MainScreen()
{
  lcd.clrscr(BLACK);
  
  for(int i = 0; i < MAX_BUTTONS; i++)
  {
    _buttons[i].Draw();
  }

  _statusPanel.Draw();
  _resultPanel.Draw();
}

void ScreenCustom::PollScreen()
{
  word x, y;
  ButtonIds buttonId = BUTTON_INVALID;
  if(digitalRead(2) == 0)
  {
    lcdtouch.readxy();
    x = lcdtouch.readx();
    y = lcdtouch.ready();
    
    for(int i = 0; i < MAX_BUTTONS; i++)
    {
      if(_buttons[i].IsClicked(x, y))
      {
          buttonId = _buttons[i].GetId();
          break;
      }
    }
  }
  
  switch (buttonId)
    {
      case BUTTON_RAW_COLOR: RawColorReq(); break;
      case BUTTON_TEMP: TemperatureReq(); break;
      case BUTTON_HEIGHT: HeightReq(); break;
      case BUTTON_BUZZ_ON: BuzzOnReq(); break;
      case BUTTON_BUZZ_OFF: BuzzOffReq(); break;
      default: break;
    }
}
