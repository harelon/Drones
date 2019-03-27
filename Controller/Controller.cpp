#include <Controller.h>
Controller::Controller(uint8_t rx,uint8_t tx):Comms(rx,tx)
{

}

void Controller::RequestForTemperature()
{
    TemperatureRequest request;

    request.header.length = sizeof(TemperatureRequest);
    request.header.type = REQUEST_FOR_TEMPERATURE;

    SendMessage(&request.header);
}

void Controller::RequestForColor()
{
    ColorRequest request;

    request.header.length = sizeof(ColorRequest);
    request.header.type = REQUEST_FOR_COLOR;

    SendMessage(&request.header);
}

void Controller::RequestRawColor()
{
    RawColorRequest request;

    request.header.length = sizeof(RawColorRequest);
    request.header.type = REQUEST_RAW_COLOR;

    SendMessage(&request.header);
}

void Controller::RequestForHeight()
{
    HeightRequest request;

    request.header.length = sizeof(HeightRequest);
    request.header.type = REQUEST_FOR_HEIGHT;

    SendMessage(&request.header);
}

void Controller::RequestForBuzzOn()
{
    BuzzRequest request;

    request.header.length = sizeof(BuzzRequest);
    request.header.type = REQUEST_BUZZ_ON;

    SendMessage(&request.header);
}

void Controller::RequestForBuzzOff()
{
    BuzzRequest request;

    request.header.length = sizeof(BuzzRequest);
    request.header.type = REQUEST_BUZZ_OFF;

    SendMessage(&request.header);
}

void Controller::RequestForGyro()
{
    GyroRequest request;

    request.header.length = sizeof(GyroRequest);
    request.header.type = REQUEST_ANGULAR_ORIENTATION;

    SendMessage(&request.header);
}

void Controller::RequestForServoDrop(ServoColors color)
{
    ServoRequest request;

    request.header.length = sizeof(ServoRequest);
    request.header.type = REQUEST_SERVO_DROP;
    request.servoColor = color;

    SendMessage(&request.header);
}

void Controller::DispatchMessage(MessageHeader* message)
{
    switch (message->type)
    {
        case RESPONSE_FOR_TEMPERATURE:
            OnTemperatureResponse((TemperatureResponse*)message);
            break;
        case RESPONSE_FOR_COLOR:
            OnColorResponse((ColorResponse*)message);
            break;
         case RESPONSE_RAW_COLOR:
            OnRawColorResponse((RawColorResponse*)message);
            break;
        case RESPONSE_FOR_HEIGHT:
            OnHeightResponse((HeightResponse*)message);
            break;
        case RESPONSE_BUZZ_ON:
            OnBuzzResponse((BuzzResponse*)message);
            break;
        case RESPONSE_BUZZ_OFF:
            OnBuzzResponse((BuzzResponse*)message);
            break;
        case RESPONSE_ANGULAR_ORIENTATION:
            OnGyroResponse((GyroResponse*) message);
            break;
        case RESPONSE_SERVO_DROP:
            OnServoResponse((ServoResponse*) message);
            break;
    }
}
