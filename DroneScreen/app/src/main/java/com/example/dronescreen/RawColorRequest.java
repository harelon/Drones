package com.example.dronescreen;

public class RawColorRequest extends MessageHeader {
    public RawColorRequest()
    {
        super(2,Type.REQUEST_RAW_COLOR);
    }
}
