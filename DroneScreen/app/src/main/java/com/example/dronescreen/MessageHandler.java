package com.example.dronescreen;

public class MessageHandler {
    private static ReadWriteThread _thread;
    private static MessageHeader[] _messages = new MessageHeader[]{new HeightRequest()};
    public static int obtainMessage(int count, byte[] buffer)
    {
        int index = buffer[1];
        _messages[index].deserialize(buffer);
        return index;
    }
    public static void sendMessage(MessageHeader message)
    {
        _thread.write(message.serialize());
    }
    public static void setThread(ReadWriteThread thread)
    {
        _thread = thread;
    }
    public static  MessageHeader[] getMessages()
    {
        return _messages;
    }
}
