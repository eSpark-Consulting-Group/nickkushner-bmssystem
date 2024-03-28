#include<math.h>
#include <bq769x0.h>

#define Wire Wire5
#define ntc C964951 //C394024 or C964951
#define socMethod Voltage // Voltage Or Current
#define Rx PIN_PB1
#define Tx PIN_PB0
#define BMS_I2C_ADDRESS 0x18
#define BMS_ALERT_PIN PIN_PC2

SoftwareSerial mySerial(Rx, Tx); // RX, TX
bq769x0 BMS(bq76920, BMS_I2C_ADDRESS, ntc);    // battery management system object

const int interval=250;
int count=0;
char swTxBuffer[128];
char swRxBuffer[128];
float V1,V2;
const uint64_t capacity = 2500*3600;
double I,Q,SOC,Soc_C=100,Soc_V=100;
unsigned long previousMillis = 0, previousMillis1 = 0;

void setup()
{
  mySerial.begin(9600);
   while (!mySerial) {};
  mySerial.println("BMS SYSTEM");
  Wire.setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  Wire.setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  BMS.begin(BMS_ALERT_PIN);//,BMS_BOOT_PIN
  BMS.setShuntResistorValue(1);//mOhm
}

void loop()
{
  unsigned long currentMillis = millis();
  V1 = BMS.getBatteryVoltage()/1000; //V
  if(currentMillis-previousMillis >=interval)
  {
    previousMillis = currentMillis;
    BMS.update();
    V2 = BMS.getBatteryVoltage()/1000; //V
    I = BMS.getBatteryCurrent();      //mA
  }
  BMS.enableCharging();BMS.enableDischarging();
  if(!BMS.checkStatus());
  {
    for(int i=1;i<=5;i++)
    {
      if(i==3 || i==4)
        continue;
      else
        mySerial.print("Cell Voltage: ");mySerial.print(i);mySerial.print(": ");mySerial.print(BMS.getCellVoltage((byte)i));mySerial.println("V");
    }
    mySerial.print("Battery Voltage: ");mySerial.print(V2);mySerial.println("V");
    mySerial.print("Battery Current: ");mySerial.print(I);mySerial.println("mA");
    mySerial.print("Max Cell Voltage: ");mySerial.print(BMS.getMaxCellVoltage());mySerial.println("V");
    mySerial.print("Min Cell Voltage: ");mySerial.print(BMS.getMinCellVoltage());mySerial.println("V");
    mySerial.print("Temperature in °C: ");mySerial.print(BMS.getTemperatureDegC());mySerial.println("°C");
    mySerial.print("Temperature °F: ");mySerial.println(BMS.getTemperatureDegF());
    if(count>1)
    {
      switch(socMethod)
      {
        case Voltage:
        {
          float estimatedVoltage = V2 / 3;
          Soc_V = ((estimatedVoltage - 3.0) / (4.2 - 3.0)) * 100.0; // Assuming 3.0V as minimum voltage & 4.2V as maximum
          mySerial.print("SOC: ");mySerial.print(Soc_V);mySerial.println("%");
          break;
        }

        case Current:
        {
          if(I<0 && (V2-V1)<0) //discharging
          {
            unsigned long currentMillis1 = millis();
            unsigned long t1 = currentMillis1-previousMillis1;
            Q = ((I)*(t1/1000));
            SOC = (1-Q/capacity)*100; 
            Soc_C -= SOC;
            previousMillis1 = currentMillis;
            // mySerial.print("Time: ");mySerial.print(t1);mySerial.println("ms");
          }
          else if(I>0 && (V2-V1)>0) //charging
          {
            unsigned long currentMillis1 = millis();
            unsigned long t1 = currentMillis1-previousMillis1;
            Q = ((I)*(t1/1000));
            SOC = (Q/capacity)*100; 
            Soc_C -= SOC;
            previousMillis1 = currentMillis;
            // mySerial.print("Time: ");mySerial.print(t1);mySerial.println("ms");
          }
          mySerial.print("SOC: ");mySerial.print(Soc_C);mySerial.println("%");
          break;
        }
      }
    }
    ++count;
  }
  mySerial.println();
}