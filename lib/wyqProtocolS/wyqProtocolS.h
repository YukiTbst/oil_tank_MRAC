#include "HardwareSerial.h"
#ifndef WYQPROTOCOLS
#define WYQPROTOCOLS
#include "Arduino.h"
#include "CRC.h"
#include <HardwareSerial.h>
class messenger
{
protected:
    HardwareSerial* ser;
    void waitForMessage(uint32_t maxDelay);
    byte datasToSend[255];
    byte sendLen;
public:
    byte datasReceived[255];
    byte recLen;
    messenger(HardwareSerial* ctlSer);
    void waitForIncoming(uint32_t maxDelay);
    void send(byte* bytep, byte len);
};
#endif