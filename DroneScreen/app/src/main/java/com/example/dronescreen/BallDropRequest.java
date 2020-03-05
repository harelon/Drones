package com.example.dronescreen;

public class BallDropRequest extends MessageHeader {
    public BallDropRequest() {
        super(2, Type.REQUEST_SERVO_DROP);
    }
}
