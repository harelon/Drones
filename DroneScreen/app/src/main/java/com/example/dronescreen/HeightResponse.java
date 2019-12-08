package com.example.dronescreen;

public class HeightResponse extends MessageHeader {
    private int _height;
    public HeightResponse(int height)
    {
        super(4,Type.RESPONSE_FOR_HEIGHT);
        _height = height;
    }

    public HeightResponse(byte [] buffer)
    {
        super(buffer);
        _height = buffer[2]<<8;
        _height += buffer[3];
    }

    public int getHeight()
    {
        return _height;
    }
}
