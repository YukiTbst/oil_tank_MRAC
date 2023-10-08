#ifndef ESCCONTROLLERDRIVER
#define ESCCONTROLLERDRIVER
#include "Arduino.h"
#include "HardwareSerial.h"
class EscDriver
{
    protected:
    HardwareSerial controllerSer;
    public:
    EscDriver(HardwareSerial &ser);
    void stopAll();
    void setThrottle(int idx, float throttle);
    void calibrateAll();
};
#endif
