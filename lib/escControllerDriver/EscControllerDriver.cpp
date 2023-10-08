#include "EscControllerDriver.h"
#include "WyqProtocol.h"
EscDriver::EscDriver(HardwareSerial &ser):controllerSer(ser)
{
    controllerSer.begin(500000);
}
void EscDriver::setThrottle(int idx, float throttle)
{
    String cHead="wyq";
    String cmd=cHead+"N"+String(idx)+"eW"+String(throttle)+"e";
    check_bytes_append(cmd);
    controllerSer.println(cmd);
    return;
}
void EscDriver::stopAll()
{
    for(int i=0;i<8;i++)
    {
        setThrottle(i, 0);
    }
    return;
}
void EscDriver::calibrateAll()
{
    for(int i=0;i<8;i++)
    {
        setThrottle(i, 100);
    }
    delay(5000);
    for(float i=100;i>=0;i=i-0.1)
    {
        for(int j=0;j<8;j++)
        {
            setThrottle(j, i);
        }
        delay(2);
    }
    return;
}