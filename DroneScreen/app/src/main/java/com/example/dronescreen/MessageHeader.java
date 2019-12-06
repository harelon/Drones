package com.example.dronescreen;

class MessageHeader {
    protected enum Type
    {
        DRONE_CONNECTED(0),
        REQUEST_FOR_TEMPERATURE(1),
        RESPONSE_FOR_TEMPERATURE (2),
        REQUEST_FOR_COLOR( 3),
        RESPONSE_FOR_COLOR (4),
        REQUEST_RAW_COLOR (5),
        RESPONSE_RAW_COLOR (6),
        REQUEST_FOR_HEIGHT ( 7),
        RESPONSE_FOR_HEIGHT (8),
        REQUEST_BUZZ_ON (9),
        RESPONSE_BUZZ_ON (10),
        REQUEST_BUZZ_OFF (11),
        RESPONSE_BUZZ_OFF (12),
        REQUEST_ANGULAR_ORIENTATION (13),
        RESPONSE_ANGULAR_ORIENTATION (14),
        REQUEST_SERVO_DROP (15),
        RESPONSE_SERVO_DROP(16);

        private final byte _typeNumber;
        Type(int typeNumber) {
            _typeNumber = (byte)typeNumber;
        }
        byte toByte()
        {
            return _typeNumber;
        }
    }
    private Byte _length;
    private Type _type;

    public MessageHeader()
    {
        _length = null;
        _type = null;
    }

    public MessageHeader(int length, Type type)
    {
        _length = (byte)length;
        _type = type;
    }

    public void setLength(int length)
    {
     _length = (byte)length;
    }

    public Byte getLength()
    {
        return _length;
    }

    public void writeTo(byte[] data)
    {
        data[0] = _length;
        data[1] = _type.toByte();
    }

    public byte[] serialize()
    {
        return new byte[]{_length,_type.toByte()};
    }
    public  void load(byte[] buffer)
    {
        _length = buffer[0];
        _type = Type.values()[buffer[1]];
    }
}
