#include <Comms.h>

Comms::Comms(uint8_t rx, uint8_t tx) : _serial(rx, tx)
{    
    _serial.begin(9600);
}


void Comms::SendMessage(MessageHeader* message)
{   
    byte* p = (byte*)message;
    byte* end = p+message->length;
    while(p < end)
    {
        _serial.write(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    if(_serial.available()>0)
    {
        if(!gotLength)
        {
            gotLength=true;
            messageSize=_serial.read();
            p=(byte*)message;
            end=p+messageSize;
        }
        else 
        {
            *p = _serial.read();
            p++;
        }
    }
    if(p==end)
    {
        gotLength=false;
    }    
}

void Comms::PollMessage() {
    MessageHeader message;    
    if(ReceiveMessage(&message))
    {
        DispatchMessage(&message);
    }    
}
