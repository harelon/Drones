#ifndef ScreenCustom_H
#define ScreenCustom_H

#include "spiUnit.h"
#include "TFT9341.h"
#include "touch.h"
#include <SPI.h>

#include "Controller.h"
#include "Button.h"
#include "Panel.h"

#define MAX_BUTTONS 8
#define DEFAULT_FONT_SIZE 2

class ScreenCustom : public Controller
{
    private:
        Button _buttons[MAX_BUTTONS];
        Panel _statusPanel;
        Panel _resultPanel;
    protected:
        void OnTemperatureResponse(TemperatureResponse* message) override;
        void OnRawColorResponse(RawColorResponse* message) override;
        void OnColorResponse(ColorResponse* message) override;
        void OnHeightResponse(HeightResponse* message) override;
        void OnBuzzResponse(BuzzResponse* message) override;
        void OnGyroResponse(GyroResponse* message) override;
        void OnServoResponse(ServoResponse* message) override;
        void MainScreen();
        void Mainloop();
        void BuzzOnReq();
        void BuzzOffReq();
        void HeightReq();
        void TemperatureReq();
        void RawColorReq();
        void GyroReq();
        void ServoReq(byte number);
        void ColorReq();
    public:
        ScreenCustom(uint8_t rx, uint8_t tx);
        void PollScreen();
};

#endif
