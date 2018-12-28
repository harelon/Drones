#include <Comms.h>

Comms::Comms(uint8_t rx, uint8_t tx) : _serial(rx, tx)
<<<<<<< HEAD
{    
    pMainMessage = (MessageHeader *)msgBuffer;
=======
{
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
    _serial.begin(9600);
}

void Comms::SendMessage(MessageHeader* message)
<<<<<<< HEAD
{   
    byte *p = (byte*)message;
    byte *end = p + message->length;
=======
{
    byte *p = (byte*)message;
    byte *end = p+message->length;
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
    while(p < end)
    {
        _serial.write(*p);
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
<<<<<<< HEAD
            pRecieve = (byte*)message;
            *pRecieve = _serial.read();
            gotLength = true;
            endRecieve = pRecieve + (message->length);            
=======
            pRecieve=(byte*)message;
            *pRecieve=_serial.read();
            gotLength=true;
            endRecieve=pRecieve+(message->length);
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
            pRecieve++;
        }
        else
        {
<<<<<<< HEAD
            *pRecieve = _serial.read();            
=======
            *pRecieve = _serial.read();
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
            pRecieve++;
        }
    }
    if(pRecieve==endRecieve)
<<<<<<< HEAD
    {        
        gotLength = false;  
        pRecieve = (byte*)message;      
=======
    {
        gotLength=false;
        pRecieve=(byte*)message;
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
        return true;
    }
    return false;
}

void Comms::PollMessage() {

<<<<<<< HEAD
    if(ReceiveMessage(pMainMessage))
    {        
        this->DispatchMessage(pMainMessage);
=======
    if(ReceiveMessage(&MainMessage))
    {        
        this->DispatchMessage(&MainMessage);
>>>>>>> fixed recieve message not reseting pRecieve on finish recieving
    }    
}
