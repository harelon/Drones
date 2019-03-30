#ifndef BasicSerial_H
#define BasicSerial_H

#include <Arduino.h>

#define DEFAULT_TRANSMISSION_RATE 9600

#ifdef ARDUINO_AVR_UNO
    #include <SoftwareSerial.h>
    #define ARDUINO_BOARD
#endif

class BasicSerial
{
    private:
        #ifdef ARDUINO_BOARD
            SoftwareSerial _serial;
        #endif
    public:
        #ifdef ARDUINO_BOARD
            BasicSerial(uint8_t rx, uint8_t tx);
            BasicSerial(uint8_t rx, uint8_t tx, long transmissionRate);
        #else
            BasicSerial();
            BasicSerial(long transmissionRate);
        #endif
        byte read();
        byte write(byte value);
        byte available();
};

#endif
