#include <Comms.h>

void Comms::SendMessage(MessageHeader* message)
{   
    byte *p = (byte*)message;
    byte *end = p + message->length;
    while(p < end)
    {
        _serial.write(*p);
        Serial.println("write");
        Serial.println(*p);
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
            Serial.println("read");
            Serial.println(*pRecieve);
            gotLength = true;
            endRecieve = pRecieve + (message->length);
            pRecieve++;
        }
        else
        {
            *pRecieve = _serial.read();
            Serial.println("read");
            Serial.println(*pRecieve);
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
        DispatchMessage(pMainMessage);
    }    
}
