#include<Wire.h>
#include<math.h>
#include <bq769x0.h>

#define ntc C964951 //C394024 or C964951
#define socMethod Voltage // Voltage Or Current
#define SDA PIN_PB1 //Rx
#define SCL PIN_PB0 //Tx
#define ADD1 PIN_PA4 //by default HIGH
#define ADD2 PIN_PA5 //by default HIGH
#define ADD3 PIN_PA6 //by default HIGH
#define ADD4 PIN_PA7 //by default HIGH
#define BMS_I2C_ADDRESS 0x18
#define BMS_ALERT_PIN PIN_PC2

// SoftwareSerial mySerial(SDA, SCL); // RX, TX

bq769x0 BMS(bq76920, BMS_I2C_ADDRESS, ntc);    // battery management system object

const int interval=250;
int count=0;
uint8_t ATtiny_I2C_ADDRESS =0, Ad1=1, Ad2=1, Ad3=1, Ad4=1;
char swTxBuffer[64];
char swRxBuffer[64];
float V1;
const uint64_t capacity = 2500*3600;
double Q,SOC,SOC_V=100, SOC_C=100;
unsigned long previousMillis = 0, previousMillis1 = 0;

struct bms
{
  float Bat_Voltage, Bat_Current, Temperature, Cell_Voltage1, Cell_Voltage2, Cell_Voltage3, Soc_V, Soc_C;
} bms_t;

void requestEvent() {
  Wire.write((uint8_t*)&bms_t, sizeof(bms_t));
}

void setup()
{
  pinMode(ADD1,INPUT); pinMode(ADD2,INPUT); pinMode(ADD3,INPUT); pinMode(ADD4,INPUT);
  Ad1 = digitalRead(ADD1); Ad2 = digitalRead(ADD2); Ad3 = digitalRead(ADD3); Ad4 = digitalRead(ADD4); 
  ATtiny_I2C_ADDRESS =  (((!Ad4<<1) | !Ad3)<<1 | !Ad2)<<1 | !Ad1;
  // mySerial.begin(9600);
  //  while (!mySerial) {};
  // mySerial.println("BMS SYSTEM");
  softWire.setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  softWire.setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  Wire.pins(SDA, SCL);
  Wire.begin(ATtiny_I2C_ADDRESS);
  BMS.begin(BMS_ALERT_PIN);//,BMS_BOOT_PIN
  BMS.setShuntResistorValue(1);//mOhm
  Wire.onRequest(requestEvent);
}

void loop()
{
  unsigned long currentMillis = millis();
  V1 = BMS.getBatteryVoltage()/1000; //V
  if(currentMillis-previousMillis >=interval)
  {
    previousMillis = currentMillis;
    BMS.update();
    bms_t.Bat_Voltage = BMS.getBatteryVoltage()/1000; //V
    bms_t.Bat_Current = BMS.getBatteryCurrent();      //mA
  }
  BMS.enableCharging();BMS.enableDischarging();
  if(!BMS.checkStatus());
  {
    bms_t.Temperature   = BMS.getTemperatureDegC();
    // bms_t.Min_Voltage   = BMS.getMinCellVoltage();
    // bms_t.Max_Voltage   = BMS.getMaxCellVoltage();
    bms_t.Cell_Voltage1 = BMS.getCellVoltage((byte)1);
    bms_t.Cell_Voltage2 = BMS.getCellVoltage((byte)2);
    bms_t.Cell_Voltage3 = BMS.getCellVoltage((byte)5);
    // for(int i=1;i<=5;i++)
    // {
    //   if(i==3 || i==4)
    //     continue;
    //   else
    //     mySerial.print("Cell Voltage: ");mySerial.print(i);mySerial.print(": ");mySerial.print(BMS.getCellVoltage((byte)i));mySerial.println("V");
    // }
    // mySerial.print("Battery Voltage: ");mySerial.print(V2);mySerial.println("V");
    // mySerial.print("Battery Current: ");mySerial.print(bms_t.Bat_Current);mySerial.println("mA");
    // mySerial.print("Max Cell Voltage: ");mySerial.print(BMS.getMaxCellVoltage());mySerial.println("V");
    // mySerial.print("Min Cell Voltage: ");mySerial.print(BMS.getMinCellVoltage());mySerial.println("V");
    // mySerial.print("Temperature in °C: ");mySerial.print(BMS.getTemperatureDegC());mySerial.println("°C");
    // mySerial.print("Temperature °F: ");mySerial.println(BMS.getTemperatureDegF());
    if(count>1)
    {
      switch(socMethod)
      {
        case Voltage:
        {
          float estimatedVoltage = bms_t.Bat_Voltage / 3;
          SOC_V = ((estimatedVoltage - 3.0) / (4.2 - 3.0)) * 100.0; // Assuming 3.0V as minimum voltage & 4.2V as maximum
          bms_t.Soc_V = SOC_V;
          // mySerial.print("SOC: ");mySerial.print(Soc_V);mySerial.println("%");
          break;
        }

        case Current:
        {
          if(bms_t.Bat_Current<0 && (bms_t.Bat_Voltage-V1)<0) //discharging
          {
            unsigned long currentMillis1 = millis();
            unsigned long t1 = currentMillis1-previousMillis1;
            Q = ((bms_t.Bat_Current)*(t1/1000));
            SOC = (1-Q/capacity)*100; 
            SOC_C -= SOC;
            previousMillis1 = currentMillis;
            // mySerial.print("Time: ");mySerial.print(t1);mySerial.println("ms");
          }
          else if(bms_t.Bat_Current>0 && (bms_t.Bat_Voltage-V1)>0) //charging
          {
            unsigned long currentMillis1 = millis();
            unsigned long t1 = currentMillis1-previousMillis1;
            Q = ((bms_t.Bat_Current)*(t1/1000));
            SOC = (Q/capacity)*100; 
            SOC_C -= SOC;
            previousMillis1 = currentMillis;
            // mySerial.print("Time: ");mySerial.print(t1);mySerial.println("ms");
          }
          bms_t.Soc_C = SOC_C;
          // mySerial.print("SOC: ");mySerial.print(Soc_C);mySerial.println("%");
          break;
        }
      }
    }
    ++count;
  }
}