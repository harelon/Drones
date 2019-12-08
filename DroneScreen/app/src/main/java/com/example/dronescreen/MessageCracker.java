package com.example.dronescreen;

public class MessageCracker {
    private MessageHandler _messageHandler;
    public MessageCracker(MessageHandler messageHandler)
    {
        _messageHandler = messageHandler;
    }
    public void crack(byte [] buffer)
    {
        int length = buffer[0];
        MessageHeader.Type msgType = MessageHeader.Type.values()[buffer[1]];
        switch (msgType)
        {
            case DRONE_CONNECTED:
                break;
            case RESPONSE_FOR_HEIGHT:
                HeightResponse msg = new HeightResponse(buffer);
                _messageHandler.onMessage(msg);
                break;
        }
    }
}
