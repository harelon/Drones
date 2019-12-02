package com.example.dronescreen;

public class HeightRequest extends MessageHeader {
    public HeightRequest()
    {
        super(2,Type.REQUEST_FOR_HEIGHT);
    }
}
