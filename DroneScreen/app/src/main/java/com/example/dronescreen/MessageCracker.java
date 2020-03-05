package com.example.dronescreen;

public class MessageCracker {
    private MessageHandler _messageHandler;
    public MessageCracker(MessageHandler messageHandler)
    {
        _messageHandler = messageHandler;
    }
    public void crack(byte [] buffer)
    {
        MessageHeader.Type msgType = MessageHeader.Type.values()[buffer[1]];
        switch (msgType)
        {
            case DRONE_CONNECTED:
                break;
            case RESPONSE_FOR_COLOR: {
                ColorResponse msg = new ColorResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_ANGULAR_ORIENTATION:{
                AngularOrientationResponse msg = new AngularOrientationResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_FOR_HEIGHT: {
                HeightResponse msg = new HeightResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_LED_ON: {
                LedResponse msg = new LedResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_FOR_TEMPERATURE:{
                TemperatureResponse msg = new TemperatureResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_RAW_COLOR:{
                RawColorResponse msg = new RawColorResponse(buffer);
//                _messageHandler.onMessage(msg);
                break;
            }
            case RESPONSE_SERVO_DROP:{
                BallDropResponse msg = new BallDropResponse(buffer);
                _messageHandler.onMessage(msg);
                break;
            }
        }
    }
}
