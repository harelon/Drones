#ifndef Button_H
#define Button_H

#include "spiUnit.h"
#include "TFT9341.h"

enum ButtonIds{
    BUTTON_INVALID,
    BUTTON_COLOR,
    BUTTON_TEMP,
    BUTTON_HEIGHT,
    BUTTON_BUZZ_ON,
    BUTTON_BUZZ_OFF,
};

class Button
{
    private:
        uint16_t _foreColor;
        uint16_t _backColor;
        int _x;
        int _y;
        int _width;
        int _height;
        String _text;
        ButtonIds _id;
    public:
        Button();
        void Init(ButtonIds id, int x, int y, int width, int height, String text, uint16_t foreColor, uint16_t backColor);
        bool IsClicked(int x,int y);
        ButtonIds GetId();
        void Draw();
};

#endif
