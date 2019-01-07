#include <Drone.h>
Drone::Drone(uint8_t rx,uint8_t tx):Comms(rx,tx)
{

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
    if( 
       !_LightSensor.readRedLight(red_light) ||
       !_LightSensor.readGreenLight(green_light) ||
       !_LightSensor.readBlueLight(blue_light)){
        return;
    }

    response.color.r = red_light*transmitionRate;
    response.color.g = green_light*transmitionRate;
    response.color.b = blue_light*transmitionRate;

    SendMessage(&response.header);
}

Drone* Drone::SetUpHeightSensor()
{
    return this;
}

void Drone::SendHeight()
{
    HeightResponse response;

    response.header.length = sizeof(HeightResponse);
    response.header.type = RESPONSE_FOR_HEIGHT;
    
   //response.height=;

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
    }
    Serial.println("called dispatch message");
}

void Drone::OnTemperatureRequest()
{
    SendTemperature();
}

void Drone::OnColorRequest()
{
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
