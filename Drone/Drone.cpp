#include <Drone.h>
Drone::Drone(uint8_t rx,uint8_t tx):Comms(rx,tx)
{        
    Wire.begin();    
}

Drone* Drone::SetUpTempSensor()
{
    _TempSensor.config();
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
    return this;
}

void Drone::SendColor()
{
    ColorResponse response;

    response.header.length = sizeof(ColorResponse);
    response.header.type = RESPONSE_FOR_COLOR;

    response.color.r = red_light*transmitionRate;
    response.color.g = green_light*transmitionRate;
    response.color.b = blue_light*transmitionRate;

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

Drone* Drone::SetUpHeightSensor(int echo, int trig)
{
    _trig = trig;
    _echo = echo;
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    return this;
}

void Drone::SendHeight()
{
    HeightResponse response;
   
    response.header.length = sizeof(HeightResponse);
    response.header.type = RESPONSE_FOR_HEIGHT;

    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);
    response.height = pulseIn(_echo, HIGH) / 2 / 28;
    SendMessage(&response.header);
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

Drone* Drone::SetUpBuzzer(int buzzerId)
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
    response.angularOrientation.pitch = _Gyro.GetPitch();
    response.angularOrientation.roll = _Gyro.GetRoll();
    response.angularOrientation.yaw = _Gyro.GetYaw();
    SendMessage(&response.header);
}

Drone* Drone::SetUpGyro()
{
    _Gyro.begin();
    return this;
}

Drone* Drone::SetUpLeds(byte pin)
{    
    cl.SetPin(pin);
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
    }
}

void Drone::OnTemperatureRequest()
{
    SendTemperature();
}

void Drone::OnColorRequest()
{
    ReadColor();
    _sensedColor = Utils::RGB2MainColor(red_light, green_light, blue_light);
    _cl.SetAll(_sensedColor);
    SendColor();
}

void Drone::OnHeightRequest()
{
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
