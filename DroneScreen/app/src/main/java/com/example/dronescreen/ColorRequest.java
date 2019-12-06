package com.example.dronescreen;

public class ColorRequest extends MessageHeader {
    public ColorRequest()
    {
        super(2, Type.REQUEST_FOR_COLOR);
    }
}
