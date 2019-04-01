#include <Drone.h>

Drone* Drone::SetUpServo(byte pin, ServoColors color)
{
   return SetUpServo(pin, color, NEED_TO_LOAD);
}

Drone* Drone::SetUpServo(byte pin, ServoColors color, BallStates state)
{
    balls[color].Init(pin, color, state);
    balls[color].Lock();
    return this;
}

void Drone::SendBallDrop(ServoRequest* message)
{
    ServoResponse response;

    response.header.length = sizeof(ServoResponse);
    response.header.type = RESPONSE_SERVO_DROP;
    
    
    response.state = DropBall(message->servoColor);

    SendMessage(&response.header);
}

BallStates Drone::DropBall(ServoColors color)
{
    return balls[color].Drop();
}

Drone* Drone::SetUpTempSensor()
{
    _TempSensor.config();
    if(Serial)
    {
        Serial.println("temperature sensor begun");
    }
    return this;
}

void Drone::SendTemperature()
{
    TemperatureResponse response;

    response.header.length = sizeof(TemperatureResponse);
    response.header.type = RESPONSE_FOR_TEMPERATURE;
    
    _TempSensor.readTempHumid();
    response.temperature = _TempSensor.getTemp();

    SendMessage(&response.header);
}

Drone* Drone::SetUpColorSensor()
{
    _LightSensor = SparkFun_APDS9960();
    _LightSensor.init();
    _LightSensor.enableLightSensor(false);
    if(Serial)
    {
        Serial.println("color sensor begun");
    }
    return this;
}

void Drone::SendRawColor()
{
    RawColorResponse response;

    response.header.length = sizeof(RawColorResponse);
    response.header.type = RESPONSE_RAW_COLOR;

    response.color.r = red_light;
    response.color.g = green_light;
    response.color.b = blue_light;

    SendMessage(&response.header);
}

void Drone::SendColor()
{
    ColorResponse response;

    response.header.length = sizeof(ColorResponse);
    response.header.type = RESPONSE_FOR_COLOR;
    response.color = _sensedColor;

    SendMessage(&response.header);
}

void Drone::ReadColor()
{
    if( 
       !_LightSensor.readRedLight(red_light) ||
       !_LightSensor.readGreenLight(green_light) ||
       !_LightSensor.readBlueLight(blue_light)){ 
        red_light = 0;
        green_light = 0;
        blue_light = 0;
        return;
       }
    red_light = red_light * transmitionRate;
    green_light = green_light * transmitionRate;
    blue_light = blue_light * transmitionRate;
}

Drone* Drone::SetUpHeightSensor(byte echo)
{
    _echo = echo;
    pinMode(_echo, INPUT);
    if(Serial)
    {
        Serial.println("height sensor begun");
    }
    return this;
}

void Drone::SendHeight()
{
    HeightResponse response;
   
    response.header.length = sizeof(HeightResponse);
    response.header.type = RESPONSE_FOR_HEIGHT;
    response.height = _height;
    SendMessage(&response.header);
}

void Drone::SenseHeight()
{
    _height = pulseIn(_echo, HIGH) / 2 / 28;
}

void Drone::TurnBuzzerOff()
{
    digitalWrite(_buzzerId, LOW);
    BuzzResponse response;
    response.header.length = sizeof(BuzzResponse);
    response.header.type = RESPONSE_BUZZ_OFF;
    SendMessage(&response.header);
}

void Drone::TurnBuzzerOn()
{
    digitalWrite(_buzzerId, HIGH);
    BuzzResponse response;
    response.header.length = sizeof(BuzzResponse);
    response.header.type = RESPONSE_BUZZ_ON;
    SendMessage(&response.header);
}

Drone* Drone::SetUpBuzzer(byte buzzerId)
{
    _buzzerId = buzzerId;
    pinMode(_buzzerId, OUTPUT);
    return this;
}

void Drone::SendAngularOrientation()
{
    GyroResponse response;
    response.header.length = sizeof(GyroResponse);
    response.header.type = RESPONSE_ANGULAR_ORIENTATION;
    response.angularOrientation.pitch = (int16_t)_Gyro.GetPitch();
    response.angularOrientation.roll = (int16_t)_Gyro.GetRoll();
    response.angularOrientation.yaw = (int16_t)_Gyro.GetYaw();
    SendMessage(&response.header);
}

Drone* Drone::SetUpGyro()
{
    _Gyro.begin();
    if(Serial)
    {
        Serial.println("gyro begun");
    }
    return this;
}

Drone* Drone::SetUpLeds(byte pin)
{
    _cl.SetPin(pin);
    _cl.begin();
    if(Serial)
    {
        Serial.println("leds begun");
    }
    _cl.SetAll(0xFFFFFF);
    delay(1000);
    _cl.TurnOffLed();
    return this;
}

void Drone::DispatchMessage(MessageHeader* message)
{
    switch (message->type)
    {
        case REQUEST_FOR_TEMPERATURE:
            OnTemperatureRequest();
            break;
        case REQUEST_FOR_COLOR:
            OnColorRequest();
            break;
        case REQUEST_RAW_COLOR:
            OnRawColorRequest();
            break;
        case REQUEST_FOR_HEIGHT:
            OnHeightRequest();
            break;
        case REQUEST_BUZZ_ON:
            OnBuzzerOnRequest();
            break;
        case REQUEST_BUZZ_OFF:
            OnBuzzerOffRequest();
            break;
        case REQUEST_ANGULAR_ORIENTATION:
            OnAngularOrientationRequest();
            break;
        case REQUEST_SERVO_DROP:
            OnBallDropRequest((ServoRequest*) message);
            break;
    }
}

void Drone::SendConnectMsg()
{
    DroneConnected msg;
    msg.header.length = sizeof(DroneConnected);
    msg.header.type = DRONE_CONNECTED;

    SendMessage(&msg.header);
}

void Drone::OnTemperatureRequest()
{
    SendTemperature();
}

void Drone::OnColorRequest()
{
    ReadColor();
    _sensedColor = Utils::RGB2MainColor(red_light, green_light, blue_light);
    SendColor();
}

void Drone::OnHeightRequest()
{
    SenseHeight();
    SendHeight();
}

void Drone::OnBuzzerOnRequest()
{
    TurnBuzzerOn();
}

void Drone::OnBuzzerOffRequest()
{
    TurnBuzzerOff();
}

void Drone::OnAngularOrientationRequest()
{
    SendAngularOrientation();
}

void Drone::OnRawColorRequest()
{
    ReadColor();
    SendRawColor();
}

void Drone::OnBallDropRequest(ServoRequest* message)
{
    SendBallDrop(message);
}
