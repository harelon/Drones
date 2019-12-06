package com.example.dronescreen;

public class ServoDropRequest extends MessageHeader {
    byte ballDrop;
    public ServoDropRequest(byte ballDrop)
    {
        super(3,Type.REQUEST_SERVO_DROP);
    }
}
