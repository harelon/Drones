package com.example.dronescreen;

public class MessageHandler {
    private static MessageHeader _message = new MessageHeader();
    private static ReadWriteThread _thread;
    public static boolean obtainMessage(int count, byte[] buffer)
    {
        if(_message.getLength()==null) {
            _message.setLength(buffer[0]);
        }
        if(count >= _message.getLength())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    public static void sendMessage(MessageHeader message)
    {
        _thread.write(message.serialize());
    }
    public static void setThread(ReadWriteThread thread)
    {
        _thread = thread;
    }
}
