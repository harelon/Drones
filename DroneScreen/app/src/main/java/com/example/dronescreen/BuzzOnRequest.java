package com.example.dronescreen;

public class BuzzOnRequest extends MessageHeader {
    public BuzzOnRequest()
    {
        super(2,Type.REQUEST_BUZZ_ON);
    }
}
