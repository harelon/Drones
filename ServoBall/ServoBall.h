#ifndef ServoBall_H
#define ServoBall_H

#include "Utils.h"
#include "Servo.h"

class ServoBall
{
    private:
        byte _pin;
        ServoColors _color;
        BallStates _state;
        Servo _servo;
    public:
        ServoBall();
        void Init(byte pin, ServoColors color);
        void Init(byte pin, ServoColors color, BallStates state);
        BallStates Lock();
        BallStates Drop();
        BallStates GetState();
};

#endif
