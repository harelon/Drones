#include <Comms.h>

void Comms::SendMessage(MessageHeader* message)
{   
    byte *p = (byte*)message;
    byte *end = p + message->length;
    while(p < end)
    {
        _serial.write(*p);
        p++;
    }
}

bool Comms::ReceiveMessage(MessageHeader* message)
{
    if(_serial.available() > 0)
    {
        if(!gotLength)
        {
            pRecieve = (byte*)message;
            *pRecieve = _serial.read();
            gotLength = true;
            endRecieve = pRecieve + (message->length);            
            pRecieve++;
        }
        else
        {
            *pRecieve = _serial.read();
            pRecieve++;
        }
    }
    if(pRecieve==endRecieve)
    {        
        gotLength = false;  
        pRecieve = (byte*)message;      
        return true;
    }
    return false;
}

void Comms::PollMessage() {

    if(ReceiveMessage(pMainMessage))
    {        
        this->DispatchMessage(pMainMessage);
    }    
}
