package com.example.dronescreen;

public class HeightResponse extends MessageHeader {
    public HeightResponse()
    {
        super(4,Type.RESPONSE_FOR_HEIGHT);
    }

    @Override
    public void load(byte[] buffer) {
        super.load(buffer);
    }
}
