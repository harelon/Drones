package com.example.dronescreen;

import android.util.Log;

public class LedRequest extends MessageHeader {
    private int _color;
    private int _wingNum;
    public LedRequest(int color, int wingNum) {
        super(6,Type.REQUEST_LED_ON);
        _color = color;
        _wingNum = wingNum;
    }
    @Override
    public byte[] serialize()
    {
        Log.d("colors","r" + Integer.toHexString((byte)((_color/256)/256)));
        Log.d("colors","g" + Integer.toHexString((byte)((_color/256)%256)));
        Log.d("colors","b" + Integer.toString((byte)(_color%256)));
        return new byte[]{_length,_type.toByte(),(byte)_wingNum, (byte)((_color/256)/256),(byte)((_color/256)%256),(byte)(_color%256)};
    }
}
