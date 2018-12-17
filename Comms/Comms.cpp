#include <Comms.h>

Comms::Comms(uint8_t rx,uint8_t tx):_serial(rx,tx)
{    
    _serial.begin(9600);
}


void Comms::SendMessage(MessageHeader* message)
{   
    byte* p=(byte*)message;
    byte* end=p+message->length;
    while(p<end)
    {
        _serial.write(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    if(!(_serial.available()>0))
    {
        return false;
    }
    byte size=_serial.read();
    byte* p=(byte*)message;
    message->length=size;
    byte* end=p+size;
    p++;
    while(p<end)
    {
        *p=_serial.read();
        p++;
    }
    return true;
}