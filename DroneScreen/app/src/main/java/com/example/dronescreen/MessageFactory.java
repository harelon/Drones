package com.example.dronescreen;

public class MessageFactory {
    public static RawColorRequest getRawColorRequest()
    {
        return new RawColorRequest();
    }
    public static BuzzOffRequest getBuzzOffRequest()
    {
        return new BuzzOffRequest();
    }
}
