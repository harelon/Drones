package com.example.dronescreen;

public class TemperatureRequest extends MessageHeader {
    public TemperatureRequest()
    {
        super(2,Type.REQUEST_FOR_TEMPERATURE);
    }
}
