package com.example.dronescreen;

public class RawColorResponse extends MessageHeader {
    private int _red;
    private int _green;
    private int _blue;

    public RawColorResponse(byte[] buffer)
    {
        super(buffer);
        _red = (buffer[2]&0xFF);
        _green = (buffer[3]&0xFF);
        _blue =  (buffer[4]&0xFF);
    }
    public int getRed()
    {
        return  _red;
    }
    public int getGreen()
    {
        return  _green;
    }
    public int getBlue()
    {
        return  _blue;
    }
}
