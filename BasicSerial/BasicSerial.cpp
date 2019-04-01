#include <BasicSerial.h>

#ifdef ARDUINO_BOARD

BasicSerial::BasicSerial(uint8_t rx, uint8_t tx) : _serial(rx, tx)
{
    _serial.begin(DEFAULT_TRANSMISSION_RATE);
}

BasicSerial::BasicSerial(uint8_t rx, uint8_t tx, long transmissionRate) : _serial(rx, tx)
{
    _serial.begin(transmissionRate);
}

byte BasicSerial::read()
{
    return _serial.read();
}

byte BasicSerial::write(byte value)
{
    return _serial.write(value);
}

byte BasicSerial::available()
{
    return _serial.available();
}

#else

BasicSerial::BasicSerial()
{
    Serial.begin(DEFAULT_TRANSMISSION_RATE);
}

BasicSerial::BasicSerial(long transmissionRate)
{
    Serial.begin(transmissionRate);
}

byte BasicSerial::read()
{
    return Serial.read();
}

byte BasicSerial::write(byte value)
{
    return Serial.write(value);
}

byte BasicSerial::available()
{
    return Serial.available();
}
#endif
