package com.example.dronescreen;

public class TemperatureResponse extends  MessageHeader {
    private float _temperature;
    public TemperatureResponse(byte [] buffer)
    {
        super(buffer);
        _temperature = Float.intBitsToFloat( ((int)(buffer[2]&0xFF)) ^ ((int)(buffer[3]&0xFF))<<8 ^ ((int)(buffer[4]&0xFF))<<16 ^ ((int)(buffer[5]&0xFF))<<24 );
    }
    public float getTemperature()
    {
        return _temperature;
    }

}
