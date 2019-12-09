package com.example.dronescreen;

public interface MessageHandler {
    void onMessage(ColorResponse msg);
    void onMessage(HeightResponse msg);
}
