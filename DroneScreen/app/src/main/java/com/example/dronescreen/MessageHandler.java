package com.example.dronescreen;

public class MessageHandler {
    public static int MESSAGE_READ = 0;
    public static int MESSAGE_WRITE = 1;
    private MessageHeader message;
    public MessageHandler obtainMessage(int messageType, int count, byte[] buffer)
    {

        return this;
    }
    public void sendToTarget()
    {

    }
}
