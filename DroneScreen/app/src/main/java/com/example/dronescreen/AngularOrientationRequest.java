package com.example.dronescreen;

public class AngularOrientationRequest extends MessageHeader {
    public AngularOrientationRequest()
    {
        super(2,Type.REQUEST_ANGULAR_ORIENTATION);
    }
}
