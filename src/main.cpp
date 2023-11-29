#include <Arduino.h>
#include "MRAC_for_coder_slower.h"
#include "MRAC_for_coder_slower_private.h"
#include "rtwtypes.h"
#include "Wire.h"
#include <SPI.h>
#include "YKcontroller.h"
#include "EEPROM.h"
#include "command_processor.h"
#include "EscControllerDriver.h"
#include "wyqProtocolS.h"
union imuData2Byte//用来切换imu数据与字节的union
{
  float datasF[5];
  byte datasB[20];
};
union float2Byte//用于切换浮点数和字节的union
{
  float fData;
  byte bData[4];
};
float2Byte refVal;
float2Byte ctrlOutVal;
float2Byte anti_force_m;
float2Byte anti_force_d;
//电调驱动器指针
EscDriver* escCs;//escCs means [ESC] [c]ontroller[s]
HardwareSerial controllerSerial(1);//与另一片esp32的通信串口
void motor_driver(void * parameter)//控制器，需要加入回传控制信号的功能
{
  messenger imuMessenger(&controllerSerial);
  imuData2Byte imuData;
  portTickType PrevWakeTime=xTaskGetTickCount();
  Serial.println("initiating");
  escCs->stopAll();
  Serial.println("initiated");
  controller_PID controller1(paramenters[KP], paramenters[KI], paramenters[KD]);
  imuMessenger.send(imuData.datasB, 0);//发送信号量，请求imu数据
  //初始化状态空间模型
  while(1)
  {
    imuMessenger.waitForIncoming(2);
    if(imuMessenger.recLen!=20)
    {
        Serial.println("imu data not received");
        while(controllerSerial.available())
        {
            controllerSerial.read();
        }
        delay(1000);
        imuMessenger.send(imuData.datasB, 0);
    }
    else
    {
        for(int i=0; i<20;i++)
        {
        imuData.datasB[i]=imuMessenger.datasReceived[i];
        }
        paramenters[THETA]=imuData.datasF[2];
        paramenters[OMEGA]=imuData.datasF[3];
        paramenters[BETA]=imuData.datasF[4];
        MRAC_for_code__InitialCondition[0]=paramenters[THETA];
        MRAC_for_code__InitialCondition[1]=paramenters[OMEGA];
        break;
    }
  }
  MRAC_for_coder_slower_initialize();
    //MRAC_for_coder_slower_step();

  //Serial.println(MRAC_for_code_controller_output);
  //paramenters[REF]=paramenters[THETA];
  paramenters[REF]=0;
  PrevWakeTime=xTaskGetTickCount();
  while(1)
  {
      vTaskDelayUntil(&PrevWakeTime, 10);
      if(stop)
      {
          imuData.datasB[0]=0x00;
          imuMessenger.send(imuData.datasB, 1);//发送指令，表示当前不可以往内存卡写入数据
          escCs->stopAll();
          continue;
      }
      else
      {
          imuData.datasB[0]=0x01;
          imuMessenger.send(imuData.datasB, 1);//发送指令，表示当前可以往内存卡写入数据
          imuMessenger.send(imuData.datasB, 0);//发送信号量，请求imu数据
          imuMessenger.waitForIncoming(2);
          if(imuMessenger.recLen!=20)
          {
              Serial.println("imu data not received");
          }
          else
          {
              for(int i=0; i<20;i++)
              {
              imuData.datasB[i]=imuMessenger.datasReceived[i];
              }
              paramenters[THETA]=imuData.datasF[2];
              paramenters[OMEGA]=imuData.datasF[3];
              paramenters[BETA]=imuData.datasF[4];
          }
          //   MRAC_for_coder_slower_ref=paramenters[REF];
        //   MRAC_for_coder_slower__A[1]=-paramenters[KP]*paramenters[KP];//kp:极点的相反数
        //   MRAC_for_coder_slower__A[3]=-2*paramenters[KP];
        //   MRAC_for_coder_slowe_Gain1_Gain=paramenters[KI];//前馈
        //   MRAC_for_coder_slower_Gain_Gain=paramenters[KD];//反馈
        //   MRAC_for_coder_slower_theta=paramenters[THETA];
        //   MRAC_for_coder_slower_omega=paramenters[OMEGA];
        //   MRAC_for_coder_slower_step();
        //   float vel_ref=MRAC_for_code_controller_output;
        controller1.ref_set(paramenters[REF]);
            controller1.p_set(paramenters[KP]);
            controller1.i_set(paramenters[KI]);
            controller1.d_set(paramenters[KD]);
            float vel_ref=controller1.run_one_step(paramenters[THETA], paramenters[OMEGA]);
          paramenters[U]=vel_ref;
          float vels[4];//前两个用于航向角调整，后两个用于模拟反力
          if(vel_ref>=0)
          {
              vels[0]=vel_ref;
              vels[1]=0;
          }
          else
          {
              vels[0]=0;
              vels[1]=-vel_ref;
          }
          vels[2] = paramenters[FORCE_MEAN] + paramenters[FORCE_DELTA]/2;
          vels[3] = vels[2] - paramenters[FORCE_DELTA];
          for(int i=0;i<4;i++)
          {
              vels[i]+=20;
              if(vels[i]<20)
              {
                  vels[i]=20;
              }
              if(vels[i]>100)
              {
                  vels[i]==100;
              }
              escCs->setThrottle(i, vels[i]);
          }
          refVal.fData=paramenters[REF];
          ctrlOutVal.fData=vels[0]-vels[1];
          anti_force_m.fData = paramenters[FORCE_MEAN];
          anti_force_d.fData = paramenters[FORCE_DELTA];
          byte buffer[16];
          for(int i=0;i<4;i++)
          {
              buffer[i]=refVal.bData[i];
              buffer[i+4]=ctrlOutVal.bData[i];
              buffer[i+8] = anti_force_m.bData[i];
              buffer[i+12] = anti_force_d.bData[i];
          }
          imuMessenger.send(buffer, 16);
      }
    }
}

//带校验位的指令收发
void command_reader(void * parameter)
{
    while(1)
    {
      if(!Serial.available())
      {
        delay(10);
        continue;
      }
        String str=Serial.readStringUntil('\n');
        if(str.length()<2)
        {
            if(str.length()==1)//单个字符的命令
            {
                char c1 = str[0];
                switch(c1)
                {
                    case 's':
                    stop=true;//输入stop急停
                    break;
                    case 'e':
                    stop=false;//输入enable启动
                    break;
                    case 'p':
                    s_print=!s_print;
                    break;
                    default:
                    break;
                }
            }
            continue;
        }
        else
        {
            if(command_check(str))
                {
                    float p=paramenters[KP];
                    float i=paramenters[KI];
                    float d=paramenters[KD];
                    command_process(str);
                    if(p!=paramenters[KP])
                    {
                        EEPROM.writeFloat(0, paramenters[KP]);
                        delay(1);
                        EEPROM.commit();      
                    }
                    if(i!=paramenters[KI])
                    {
                        EEPROM.writeFloat(sizeof(float), paramenters[KI]);
                        delay(1);
                        EEPROM.commit();     
                    }
                    if(d!=paramenters[KD])
                    {
                        EEPROM.writeFloat(sizeof(float)*2, paramenters[KD]);
                        delay(1);
                        EEPROM.commit();     
                    }
                }
        }
    }

}
void data_publisher(void * parameter)
{
    while(1)
    {
        if(((int) paramenters[PUBLISH_FREQ])<=0)
        {
            paramenters[PUBLISH_FREQ]=1;
        }
        delay(1000/((int) paramenters[PUBLISH_FREQ]));
        String pub_str="wyq";
        for(int i=0;i<paramenters_num;i++)
        {
            if(read_modes[i]!=0)
            {
                read_modes[i]%=2;
                pub_str+='N'+String(i)+'e'+'R'+String(paramenters[i], 3)+'e';
            }
        }
        if(pub_str=="wyq")
        {
            continue;
        }
        pub_str+=check_bytes_cal(pub_str);
        Serial.print(pub_str);
        
    }
    
}

//测试用的任务
void task_for_test(void * parameter)
{
    while(1)
    {
        if(Serial.available())
        {
            String str=Serial.readStringUntil('\n');
            if(str.length()>0)
            {
                if(command_check(str))
                {
                    Serial.println("ok");
                    command_process(str);
                }
                else
                {
                    Serial.println("fuck");
                }
            }
        }
        delay(10);
    }
    
}

void task_for_test2(void* parameter)
{
    while(1)
    {
        for(float i=0;i<100;i++)
        {
            escCs->setThrottle(1, i);
            escCs->setThrottle(0, 100-i);
            delay(100);            
        }
    }
}

//急停
void emergency_stop(void * parameter)
{
    while(1)
    {
        if(paramenters[THETA]>-3.14/2)
        {
            if(paramenters[THETA]<3.14/2)
            {
                delay(20);
                continue;
            }
        }
        escCs->stopAll();
        Serial.println("警告，摆幅超出限制！");
        ESP.restart();
    }
}


void setup() 
{
    is_test=false;
    paramenters[VEL_BAL]=50;
    escCs= new EscDriver(Serial2);
    Serial.begin(115200);
    controllerSerial.begin(500000, SERIAL_8N1, 18, 19);
    //EEPROM和PID这段其实没用，但数据收发那里可能会用到EEPROM，就把这段copy过来了
    if (!EEPROM.begin(4096)) 
    {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
    paramenters[KP]=EEPROM.readFloat(0);
    if(!(paramenters[KP]==paramenters[KP]))//如果EEPROM里没写过初值，读到的PID都是nan，nan==nan返回false
    {
        paramenters[KP]=1;
    }
    paramenters[KI]=EEPROM.readFloat(sizeof(float));
    if(!(paramenters[KI]==paramenters[KI]))
    {
        paramenters[KI]=0;
    }
    paramenters[KD]=EEPROM.readFloat(sizeof(float)*2);
    if(!(paramenters[KD]==paramenters[KD]))
    {
        paramenters[KD]=2;
    }
    if(is_test)
    {
        int testMode=0;
        while(1)
        {
            Serial.println("input test mode:");
            while(!Serial.available())
            {
              delay(1);
            }
            String cmd=Serial.readStringUntil('\n');
            if(cmd=="test0")
            {
                testMode=0;
                break;
            }
            if(cmd=="test1")
            {
                testMode=1;
                break;
            }
        }
        Serial.println("entering testmode "+String(testMode));
        switch(testMode)
        {
            case 0:
                xTaskCreatePinnedToCore(
                    task_for_test,          
                    "task_for_test",        
                    10000,            
                    NULL,             
                    5,               
                    NULL,
                    0);
                xTaskCreatePinnedToCore(
                    data_publisher,          
                    "data_publisher",        
                    10000,            
                    NULL,             
                    4,               
                    NULL,
                    0);         
            break;
            case 1:
                xTaskCreatePinnedToCore(
                    task_for_test2,          
                    "task_for_test2",        
                    10000,            
                    NULL,             
                    5,               
                    NULL,
                    0);
            break;
            default:
                Serial.println("testmode index error");
                ESP.restart();

        }
         
    }
    else
    {
        xTaskCreatePinnedToCore(
            emergency_stop,          /*任务函数*/
            "emergency_stop",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            5,                /*任务的优先级*/
            NULL,
            0); 
        xTaskCreatePinnedToCore(
            motor_driver,          /*任务函数*/
            "motor driver and controller",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            4,                /*任务的优先级*/
            NULL,
            0); 
        xTaskCreatePinnedToCore(
            command_reader,          /*任务函数*/
            "command reader",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            2,                /*任务的优先级*/
            NULL,
            1);       
        xTaskCreatePinnedToCore(
            data_publisher,          
            "data publisher",        
            10000,            
            NULL,             
            5,               
            NULL,
            1);    
        
    }
}

void loop() 
{
    delay(1000);
}

/*
void setup() {
  // put your setup code here, to run once:
  MRAC_for_coder_slower_initialize();
  MRAC_for_coder_slower_step();
}

void loop() {
  // put your main code here, to run repeatedly:
}
*/