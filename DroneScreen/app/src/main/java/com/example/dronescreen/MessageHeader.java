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

    protected byte _length;
    protected Type _type;

    protected MessageHeader(int length, Type type)
    {
        _length = (byte)length;
        _type = type;
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
}
