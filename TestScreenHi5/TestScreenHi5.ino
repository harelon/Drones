void * __dso_handle;

#include "Controller.h"
#include "SPI.h"
#include "Adafruit_ILI9341.h"
#include "SimpleTouchscreen.h"

#define NUMBER_OF_BUTTONS 7

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
//Touchscreen
#define T_SS 7
#define T_IRQ 2

static const uint8_t burst_load = 50;

enum ButtonIds {
  BUTTON_COLOR = 0,
  BUTTON_RAW_COLOR = 1,
  BUTTON_HEIGHT = 2,
  BUTTON_GYRO = 3,
  BUTTON_SERVO_RED = 4,
  BUTTON_SERVO_GREEN = 5,
  BUTTON_SERVO_BLUE = 6,
};

class ScreenLib : public Controller
{
  private:
    word x, y;
    ButtonIds _lastButtonId = -1;
    ButtonIds _currentButtonId = -1;
    Adafruit_ILI9341 lcd;
    SimpleTouchscreen lcdtouch;
    Adafruit_GFX_Button buttons[NUMBER_OF_BUTTONS];
  protected:
    void OnTemperatureResponse(TemperatureResponse* message) override{};
    void OnRawColorResponse(RawColorResponse* message) override;
    void OnColorResponse(ColorResponse* message) override;
    void OnHeightResponse(HeightResponse* message) override;
    void OnBuzzResponse(BuzzResponse* message) override{};
    void OnGyroResponse(GyroResponse* message) override;
    void OnServoResponse(ServoResponse* message) override;

    void HeightReq();
    void RawColorReq();
    void GyroReq();
    void ServoReq(ServoColors color);
    void ColorReq();
  public:
    void MainScreen();
    ScreenLib();
    void PollScreen();
};

ScreenLib::ScreenLib() : lcd(TFT_CS, TFT_DC), lcdtouch(T_IRQ, T_SS), Controller() {
  lcd.begin(5000000);
  lcdtouch.begin();
  lcd.setRotation(2);
  lcdtouch.setRotation(2);
  buttons[BUTTON_COLOR].initButton(&lcd, 60, 30, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "COLOR", 2);
  buttons[BUTTON_RAW_COLOR].initButton(&lcd, 180, 30, 120, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "RAW COLOR", 2);
  buttons[BUTTON_HEIGHT].initButton(&lcd, 60, 85, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "HEIGHT", 2);
  buttons[BUTTON_GYRO].initButton(&lcd, 180, 85, 100, 50, ILI9341_BLACK, ILI9341_YELLOW, ILI9341_BLUE, "GYRO", 2);
  buttons[BUTTON_SERVO_RED].initButton(&lcd, 60, 140, 100, 50, ILI9341_BLACK, ILI9341_RED, ILI9341_CYAN, "SERVO", 2);
  buttons[BUTTON_SERVO_GREEN].initButton(&lcd, 180, 140, 100, 50, ILI9341_BLACK, ILI9341_GREEN, ILI9341_MAGENTA, "SERVO", 2);
  buttons[BUTTON_SERVO_BLUE].initButton(&lcd, 60, 195, 100, 50, ILI9341_BLACK, ILI9341_BLUE, ILI9341_YELLOW, "SERVO", 2);
}


ScreenLib screen;

void setup() {
  screen.MainScreen();
}

void loop() {
  screen.PollScreen();
}
