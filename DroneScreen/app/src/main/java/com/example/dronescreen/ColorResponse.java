package com.example.dronescreen;

import android.util.Log;

import java.util.HashMap;

public class ColorResponse extends MessageHeader {
    private Color _color;
    private HashMap<Long,Color> map = new HashMap<Long, Color>(){
        {
            put(0x000000L, Color.BLACK);
            put(0xFF0000L,Color.RED);
            put(0x00FF00L,Color.GREEN);
            put(0x0000FFL,Color.BLUE);
            put(0xFFFFFFL,Color.WHITE);
            put(0x000001L,Color.INTERMEDIATE);
        }
    };
    enum Color
    {
        BLACK(0x000000),
        RED(0xFF0000),
        GREEN(0x00FF00),
        BLUE(0x0000FF),
        WHITE(0xFFFFFF),
        INTERMEDIATE(0x000001);
        private final long _typeNumber;
        Color(long typeNumber) {
            _typeNumber = typeNumber;
        }
        long getHex()
        {
            return _typeNumber;
        }
    }

    public ColorResponse(long color)
    {
        super(6,Type.RESPONSE_FOR_COLOR);
        _color = map.get(color);
    }

    public ColorResponse(byte [] buffer) {
        super(buffer);
        long num = 0;

        for (int i = 2 ; i <_length; i++) {
            long num2 = 0;
            if(buffer[i]==-1)
            {
                num2 = 255;
            }
            else
            {
                num2 = buffer[i];
            }
            num += (num2<<(i-2)*8);
            Log.d("num",Long.toHexString(num2));
        }
        Log.d("num",Long.toString(num));
        _color = map.get(num);
    }
    public Color getColor()
    {
        return _color;
    }
}
