package com.example.dronescreen;

import android.util.Log;

public class AngularOrientationResponse extends MessageHeader {
    private float _pitch;
    private float _roll;
    private float _yaw;
    public AngularOrientationResponse(byte[] buffer)
    {
        super(buffer);
        _pitch = Float.intBitsToFloat( (buffer[2]&0xFF) ^ (buffer[3]&0xFF)<<8 ^ (buffer[4]&0xFF)<<16 ^ (buffer[5]&0xFF)<<24 );
        _roll = Float.intBitsToFloat( (buffer[6]&0xFF) ^ (buffer[7]&0xFF)<<8 ^ (buffer[8]&0xFF)<<16 ^ (buffer[9]&0xFF)<<24 );
        _yaw =  Float.intBitsToFloat( (buffer[10]&0xFF) ^ (buffer[11]&0xFF)<<8 ^ (buffer[12]&0xFF)<<16 ^ (buffer[13]&0xFF)<<24 );
        Log.d("pitch", Float.toString(_pitch));
        Log.d("roll", Float.toString(_roll));
        Log.d("yaw", Float.toString(_yaw));
    }
    public float getPitch()
    {
        return _pitch;
    }
    public float getRoll()
    {
        return _roll;
    }
    public float getYaw()
    {
        return _yaw;
    }


}
