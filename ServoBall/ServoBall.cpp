#include <ServoBall.h>

ServoBall::ServoBall()
{
    _pin = -1;
    _color = -1;
    _state = NOT_LOADED;
}

void ServoBall::Init(byte pin, ServoColors color)
{
    Init(pin, color, NEED_TO_LOAD);
}

void ServoBall::Init(byte pin, ServoColors color, BallStates state)
{
    _pin = pin;
    _color = color;
    _state = state;
    _servo.attach(_pin);
}

BallStates ServoBall::Lock()
{
    if(_state == NEED_TO_LOAD)
    {
        _servo.write(30);
        SetState(LOADED);
    }
    return GetState();
}

BallStates ServoBall::Drop()
{
    if(_state == LOADED)
    {
        _servo.write(110);
        SetState(DROPPED);
    }
    return GetState();
}

BallStates ServoBall::GetState()
{
    return _state;
}

void ServoBall::SetState(BallStates state)
{
    _state = state;
}
