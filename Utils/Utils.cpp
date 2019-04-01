#include <Utils.h>

MainColors Utils::RGB2MainColor(uint16_t r, uint16_t g, uint16_t b)
{
    //transform color to hsv beacuse it is easier to determine which color it is
    float Rtag = r / 255.0;
    float Gtag = g / 255.0;
    float Btag = b / 255.0;
    float Cmax = max(Rtag, max(Gtag, Btag));
    float Cmin = min(Rtag, min(Gtag, Btag));
    float d = Cmax - Cmin;
    float h;
    if (d == 0)
    {
        h = 0;
    }
    else if (Cmax == Rtag)
    {
        h = 60 * ((Gtag - Btag) / d);
        if (h < 0)
        {
        h = h + 360;
        }
    }
    else if (Cmax == Gtag)
    {
        h = 60 * (((Btag - Rtag) / d) + 2);
    }
    else
    {
        h = 60 * (((Rtag - Gtag)) / d + 4);
    }   
    // if the color has low light return none which means low light
    if (Cmax < 0.4)
    {
        return MAIN_NONE;
    }
    // if the color has low saturation it is white then return white
    if (d / Cmax < 0.4)
    {
        return MAIN_WHITE;
    }
    // the hue range for green in hsv
    if (h < 180 && h > 90)
    {
        return MAIN_GREEN;
    }
    // the hue range for blue in hsv
    else if (h < 255 && h > 200)
    {
        return MAIN_BLUE;
    }
    // the hue range for red in hsv
    else if ((h > 345 && h < 360) || ( h < 11 && h > 0))
    {
        return MAIN_RED;
    }
    return MAIN_INTERMEDIATE;
}