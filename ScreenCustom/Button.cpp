#include "Button.h"

Button::Button()
{}

void Button::Init(ButtonIds id, int x, int y, int width, int height, String text, uint16_t foreColor, uint16_t backColor)
{
    _id = id;
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _text = text;
    _foreColor = foreColor;
    _backColor = backColor;
}

void Button::Draw()
{
    lcd.fillRoundRect(_x, _y, _width, _height, 5, _backColor);
    lcd.setColor(_foreColor, _backColor);
    lcd.gotoxy(_x+5, _y+10);
    lcd.print(_text);
}

bool Button::IsClicked(int x, int y)
{
    return (x >= _x && x < (_x+_width) && y >= _y && y < (_y+_height));
}

ButtonIds Button::GetId()
{
    return _id;
}
