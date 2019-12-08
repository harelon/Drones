package com.example.dronescreen;

public class ServoDropRequest extends MessageHeader {
    private byte _ballDrop;
    public ServoDropRequest(byte ballDrop)
    {
        super(3,Type.REQUEST_SERVO_DROP);
    }

    @Override
    public byte[] serialize() {
        byte [] arr = super.serialize();
        arr[2] = _ballDrop;
        return arr;
    }
}
