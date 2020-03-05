package com.example.dronescreen;

public interface MessageHandler {
//    void onMessage(ColorResponse msg);
    void onMessage(AngularOrientationResponse msg);
    void onMessage(RawColorResponse msg);
//    void onMessage(HeightResponse msg);
//    void onMessage(LedResponse msg);
//    void onMessage(TemperatureResponse msg);
}
