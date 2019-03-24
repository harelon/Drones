#include <CustomLed.h>

CustomLed cl (7);
int count = 0;
void setup()
{
    cl.begin();
}

void loop()
{
    cl.TurnOffLed();
    count = (count %  4) + 1;    
    cl.SetRing(255, 255, 255, count);
    delay(500);
}
