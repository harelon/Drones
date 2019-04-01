void * __dso_handle;

#include "Controller.h"
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
    long _lastButtonTime = -1;
    ButtonIds _currentButtonId = -1;
    Adafruit_ILI9341 lcd;
    SimpleTouchscreen lcdtouch;
    Adafruit_GFX_Button buttons[NUMBER_OF_BUTTONS];
    char result_message[20];
  protected:
    void OnConnected();

    void OnTemperatureResponse(TemperatureResponse* message) override{};
    void OnRawColorResponse(RawColorResponse* message) override;
    void OnColorResponse(ColorResponse* message) override;
    void OnHeightResponse(HeightResponse* message) override;
    void OnBuzzResponse(BuzzResponse* message) override{};
    void OnGyroResponse(GyroResponse* message) override;
    void OnServoResponse(ServoResponse* message) override;
    void OnDroneConnected() override;
    

    void HeightReq();
    void RawColorReq();
    void GyroReq();
    void ServoReq(ServoColors color);
    void ColorReq();
  public:
    void WaitForDrone() override;
    ScreenLib();
    void PollScreen();
};

ScreenLib screen;

void setup() {
  screen.WaitForDrone();
}

void loop() {
  screen.PollScreen();
  screen.PollMessage();
}
