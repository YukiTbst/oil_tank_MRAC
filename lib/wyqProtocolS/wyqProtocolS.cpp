#include "HardwareSerial.h"
#include "wyqProtocolS.h"
void messenger::waitForMessage(uint32_t maxDelay)//参量为0代表持续等候，否则参量代表等候时间
{
    uint32_t timeS=millis();
    while(!ser->available())
    {
        delay(1);
        if(maxDelay==0)
            continue;
        if(millis()-timeS>=maxDelay)
            break;
    }
    return;
}
messenger::messenger(HardwareSerial* ctlSer)
{
    ser=ctlSer; 
    datasToSend[0]=0x77;
    datasToSend[1]=0x79;
    datasToSend[2]=0x71;  
}
void messenger::waitForIncoming(uint32_t maxDelay)//清空缓冲区数据并接收新数据。参量为0代表持续等候，否则参量代表等候时间
{
    recLen=0;
    uint32_t timeS=millis();
    byte loopBuffer[256];
    byte bufferHead=0;
    byte bufferEnd=0;
    waitForMessage(maxDelay);
    bool invalid=true;
    byte state=0;
    byte len=0;
    while(invalid)
    {
        while(ser->available())
        {
            loopBuffer[bufferEnd]=ser->read();
            //Serial.write(loopBuffer[bufferEnd]);
            switch(state)
            {
                case 0:
                    if(loopBuffer[bufferEnd]==0x77)
                    {
                        bufferHead=bufferEnd;
                        state++;
                    }
                    else
                    {
                        state=0;
                    }
                    bufferEnd++;
                    break;
                case 1:
                    if(loopBuffer[bufferEnd]==0x79)
                    {
                        state++;
                    }
                    else
                    {
                        state=0;
                    }
                    bufferEnd++;
                    break;
                case 2:
                    if(loopBuffer[bufferEnd]==0x71)
                    {
                        state++;
                    }
                    else
                    {
                        state=0;
                    }
                    bufferEnd++;
                    break;
                case 3:
                    len=loopBuffer[bufferEnd]+2;
                    state++;
                    bufferEnd++;
                    break;
                case 4:
                    len--;
                    bufferEnd++;
                    if(len==0)
                    {
                        recLen=0;
                        for(byte i=0;bufferHead+i!=bufferEnd;i++)
                        {
                            datasReceived[i]=loopBuffer[bufferHead+i];
                            recLen++;
                        }
                        uint16_t crc_rec=datasReceived[recLen-1];
                        crc_rec<<=8;
                        crc_rec+=datasReceived[recLen-2];

                        // //test s
                        // for(byte i=0; i<recLen;i++)
                        // {
                        //     Serial.write(datasReceived[i]);
                        // }
                        // Serial.write(0x00ff&crc16(datasReceived, recLen-2, 0x8005, 0xffff, 0x0000, true, true));
                        // Serial.write(crc16(datasReceived, recLen-2, 0x8005, 0xffff, 0x0000, true, true)>>8);

                        // //test e

                        if(crc_rec==crc16(datasReceived, recLen-2, 0x8005, 0xffff, 0x0000, true, true))
                        {
                            recLen=recLen-6;
                            for(byte i=0;i<recLen;i++)
                            {
                                datasReceived[i]=datasReceived[i+4];
                            }
                            return;
                        }
                        state=0;
                    }
                    

            }
        }
        if(maxDelay==0)
        {
            waitForMessage(maxDelay);
            continue;
        }
        uint32_t timePast=millis()-timeS;
        if(timePast>=maxDelay)//如果maxDelay接近1<<32 -1， 可能会导致一直循环
            break;
        
    }

}
void messenger::send(byte* bytep, byte len)
{
    if(len>255-6)
        return;
    datasToSend[3]=len;
    sendLen=len+4;
    for(byte i=4;i<sendLen;i++)
    {
        datasToSend[i]=bytep[i-4];
    }
    uint16_t crc16Val=crc16(datasToSend, len+4, 0x8005, 0xffff, 0x0000, true, true);
    datasToSend[sendLen]=(0x00ff&crc16Val);
    datasToSend[sendLen+1]=crc16Val>>8;
    ser->write(datasToSend, sendLen+2);
}