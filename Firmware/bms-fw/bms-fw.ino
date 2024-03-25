/*
 This sketch is used to test UART communication between an ATTiny1616 and Arduino. 
 Using software mySerial & Servo megatinycore library to enable software mySerial within ATTiny and hardware mySerial read in arduino. 
 */

#include<math.h>
#include <bq769x0.h>

#define Wire Wire5
#define ntc C964951 //C394024 or C964951
#define Rx PIN_PB1
#define Tx PIN_PB0
#define BMS_I2C_ADDRESS 0x18
#define BMS_ALERT_PIN PIN_PC2

SoftwareSerial mySerial(Rx, Tx); // RX, TX
bq769x0 BMS(bq76920, BMS_I2C_ADDRESS, ntc);    // battery management system object

const int interval=250;
int count=0, capacity = 9000;
char swTxBuffer[128];
char swRxBuffer[128];
float V,I,Q,SOC;
unsigned long previousMillis = 0;

void setup()
{
  mySerial.begin(9600);
   while (!mySerial) {};
  mySerial.println("BMS SYSTEM");
  Wire.setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  Wire.setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  // Wire.begin();
  BMS.begin(BMS_ALERT_PIN);//,BMS_BOOT_PIN
  // BMS.setTemperatureLimits(-20, 45, 0, 45);
  BMS.setShuntResistorValue(1);//mOhm
  // BMS.setShortCircuitProtection(14000, 200);  // delay in us
  // BMS.setOvercurrentChargeProtection(8000, 200);  // delay in ms
  // BMS.setOvercurrentDischargeProtection(8000, 320); // delay in ms
  // BMS.setCellUndervoltageProtection(2600, 2); // delay in s
  // BMS.setCellOvervoltageProtection(3650, 2);  // delay in s

  // BMS.setBalancingThresholds(0, 3300, 20);  // minIdleTime_min, minCellV_mV, maxVoltageDiff_mV
  // BMS.setIdleCurrentThreshold(100);
  // BMS.enableAutoBalancing();
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis-previousMillis >=interval)
  {
    previousMillis = currentMillis;
    BMS.update();
    V = BMS.getBatteryVoltage()/1000; //V
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
    mySerial.print("Battery Voltage: ");mySerial.print(V);mySerial.println("V");
    mySerial.print("Battery Current: ");mySerial.print(I);mySerial.println("mA");
    mySerial.print("Max Cell Voltage: ");mySerial.print(BMS.getMaxCellVoltage());mySerial.println("V");
    mySerial.print("Min Cell Voltage: ");mySerial.print(BMS.getMinCellVoltage());mySerial.println("V");
    mySerial.print("Temperature in °C: ");mySerial.print(BMS.getTemperatureDegC());mySerial.println("°C");
    mySerial.print("Temperature °F: ");mySerial.println(BMS.getTemperatureDegF());
    
    // if(I<0) //discharging
    // {
    //   Q = Q+(abs(BMS.getBatteryCurrent()) * 1e-3);
    //   SOC = (1-Q/capacity)*100; 
    // }
    // else if(I>0)
    // {
    //   Q = Q+(BMS.getBatteryCurrent() * 1e-3);
    //   SOC = (Q/capacity)*100; 
    // }
    // else 
    // {
    //   SOC = 0;
    // }

    // if(I<0) //discharging
    // {
    //   Q = Q+(abs(BMS.getBatteryCurrent()) * 1e-3);
    //   SOC = (1-Q/capacity)*100;
    // }
    // else if(I>0)
    // {
    //   Q = Q+(BMS.getBatteryCurrent() * 1e-3);
    //   SOC = (Q/capacity)*100; 
    // }
    // else 
    // {
    //   SOC = 0;
    // }

    // mySerial.print("SOC: ");mySerial.print(SOC);mySerial.println("%");
  }
    mySerial.println();
}