package com.example.dronescreen;

class MessageHeader {
    protected enum Type
    {
        REQUEST_FOR_HEIGHT((byte)7);

        private final byte _typeNumber;
        Type(byte typeNumber) {
            _typeNumber = typeNumber;
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
    public static MessageHeader deserialize(byte[] buffer)
    {
        MessageHeader msg = new MessageHeader(buffer[0],Type.values()[buffer[1]]);
        switch (msg._type)
        {
            case REQUEST_FOR_HEIGHT:
                msg = (HeightRequest)msg;
        }
        return msg;
    }
}
