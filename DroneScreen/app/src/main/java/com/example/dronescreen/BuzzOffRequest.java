package com.example.dronescreen;

public class BuzzOffRequest extends MessageHeader {
    public BuzzOffRequest()
    {
        super(2,Type.REQUEST_BUZZ_OFF);
    }

}
