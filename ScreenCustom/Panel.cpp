#include "Panel.h"

Panel::Panel()
{}

void Panel::Init(int x, int y, int width, int height, String text, uint16_t foreColor, uint16_t backColor)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _text = text;
    _foreColor = foreColor;
    _backColor = backColor;
}

void Panel::Draw()
{
    lcd.fillRoundRect(_x+1, _y+1, _width-2, _height-2, 0, BLACK);
    lcd.drawRoundRect(_x, _y, _width, _height, 0, _foreColor);
    lcd.gotoxy(_x+5, _y+10);
    lcd.setColor(_foreColor, _backColor);
    lcd.print(_text);
}

void Panel::SetText(String text)
{
    _text = text;
    Draw();
}
