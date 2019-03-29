A lib that helps with the Adafruit leds.

Connect the led to 5v, gnd and a digital pin.

Public commands:
    bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte stopWing, byte stopLed);
    bool SetLeds(uint32_t color, byte startWing, byte startLed, byte stopWing, byte stopLed);
    bool SetLeds(byte redValue, byte greenValue, byte blueValue, byte startWing, byte startLed, byte numberOfLeds);
    bool SetLeds(uint32_t color, byte startWing, byte startLed, byte numberOfLeds);
    bool SetLed(byte redValue, byte greenValue, byte blueValue, byte wing, byte led);
    bool SetLed(uint32_t color, byte wing, byte led);
    bool SetWing(byte redValue, byte greenValue, byte blueValue, byte wing);
    bool SetWing(uint32_t color, byte wing);
    bool SetRing(byte redValue, byte greenValue, byte blueValue, byte radius);
    bool SetRing(uint32_t color, byte radius);
    bool SetRing(byte redValue, byte greenValue, byte blueValue, byte startRadius, byte endRadius);
    bool SetRing(uint32_t color, byte startRadius, byte endRadius);
    void SetAll(byte redValue, byte greenValue, byte blueValue);
    void SetAll(uint32_t color);
    void TurnOffLed();

Type the command begin() in setup.

can replace the RGB value with const such as:
    LED_RED
    LED_GREEN
    LED_BLUE
    LED_ORANGE
    LED_YELLOW
    LED_PURPLE
    LED_WHITE

Created 20/2/2019
modified 7/3/2019
By Yehonatan Refael Boltansky
Nes Ziona Drone Team