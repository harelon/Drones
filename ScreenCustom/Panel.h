#ifndef Panel_H
#define Panel_H

#include "spiUnit.h"
#include "TFT9341.h"

class Panel
{
    private:
        uint16_t _foreColor;
        uint16_t _backColor;
        int _x;
        int _y;
        int _width;
        int _height;
        String _text;
    public:
        Panel();
        void Init(int x, int y, int width, int height, String text, uint16_t foreColor, uint16_t backColor);
        void SetText(String text);
        void Draw();
};

#endif
