#include <Wire.h>

#define slave_address1 0x01
#define slave_address2 0x02
#define slave_address3 0x04
#define slave_address4 0x08

struct BMS
{
  float Bat_Voltage, Bat_Current, Temperature, Cell_Voltage1, Cell_Voltage2, Cell_Voltage3, Soc_V, Soc_C;
};

BMS pack_1, pack_2, pack_3, pack_4;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() 
{
  // Serial.println("Starting");
  
  // Serial.println();
  Serial.println("      BMS SYSTEM");
  Serial.println("      **********");
  byte receivedData[sizeof(pack_1)]={0};
  switch(slave_address1)
  {
    case 0x01:
      Wire.beginTransmission(slave_address1);
      Wire.requestFrom(slave_address1, sizeof(pack_1)); // Request 2 bytes from the slave
      while (Wire.available()) 
      {
        for (int i = 0; i < sizeof(pack_1); i++) 
        {
          receivedData[i] = Wire.read();
        }
      }
      Wire.endTransmission();
      memcpy(&pack_1, receivedData, sizeof(pack_1));
      pack1();
      Serial.println();
      receivedData[sizeof(pack_1)]={0};
      break;
    case 0x02:
      Wire.beginTransmission(slave_address2);
      Wire.requestFrom(slave_address2, sizeof(pack_1)); // Request 2 bytes from the slave
      // byte receivedData[sizeof(pack_1)];
      while (Wire.available()) 
      {
        for (int i = 0; i < sizeof(pack_1); i++) 
        {
          receivedData[i] = Wire.read();
        }
      }
      Wire.endTransmission();
      memcpy(&pack_2, receivedData, sizeof(pack_2));
      pack2();
      Serial.println();
      receivedData[sizeof(pack_1)]={0};
      break;
    case 0x04:
      Wire.beginTransmission(slave_address3);
      Wire.requestFrom(slave_address3, sizeof(pack_1)); // Request 2 bytes from the slave
      // byte receivedData[sizeof(pack_1)];
      while (Wire.available()) 
      {
        for (int i = 0; i < sizeof(pack_1); i++) 
        {
          receivedData[i] = Wire.read();
        }
      }
      Wire.endTransmission();
      memcpy(&pack_3, receivedData, sizeof(pack_3));
      pack3();
      Serial.println();
      receivedData[sizeof(pack_1)]={0};
      break;
    case 0x08:
      Wire.beginTransmission(slave_address4);
      Wire.requestFrom(slave_address4, sizeof(pack_1)); // Request 2 bytes from the slave
      // byte receivedData[sizeof(pack_1)];
      while (Wire.available()) 
      {
        for (int i = 0; i < sizeof(pack_1); i++) 
        {
          receivedData[i] = Wire.read();
        }
      }
      Wire.endTransmission();
      memcpy(&pack_4, receivedData, sizeof(pack_4));
      pack4();
      Serial.println();
      receivedData[sizeof(pack_1)]={0};
      break;
  }

  delay(1000); // Delay before next transmission
}

void pack1() {
  Serial.println("PACK 1:");Serial.print("Slave Address: 0x0");Serial.println(slave_address1,HEX);
  Serial.print("Battery Voltage:      ");Serial.print(pack_1.Bat_Voltage);Serial.println(" volts");
  Serial.print("Battery Current:      ");Serial.print(pack_1.Bat_Current);Serial.println(" mAmps");
  Serial.print("NTC Temperature:      ");Serial.print(pack_1.Temperature);Serial.println(" °C");
  // Serial.print("Minimum Cell Voltage: ");Serial.print(pack_1.Min_Voltage);Serial.println(" volts");
  // Serial.print("Maximum Cell Voltage: ");Serial.print(pack_1.Max_Voltage);Serial.println(" volts");
  Serial.print("Cell-1 Voltage:       ");Serial.print(pack_1.Cell_Voltage1);Serial.println(" volts");
  Serial.print("Cell-2 Voltage:       ");Serial.print(pack_1.Cell_Voltage2);Serial.println(" volts");
  Serial.print("Cell-3 Voltage:       ");Serial.print(pack_1.Cell_Voltage3);Serial.println(" volts");
  Serial.print("SOC via Voltage:      ");Serial.print(pack_1.Soc_V);Serial.println(" %");
  Serial.print("SOC via Current:      ");Serial.print(pack_1.Soc_C);Serial.println(" %");
}

void pack2() {
  Serial.println("PACK 2:");Serial.print("Slave Address: 0x0");Serial.println(slave_address2,HEX);
  Serial.print("Battery Voltage:      ");Serial.print(pack_2.Bat_Voltage);Serial.println(" volts");
  Serial.print("Battery Current:      ");Serial.print(pack_2.Bat_Current);Serial.println(" mAmps");
  Serial.print("NTC Temperature:      ");Serial.print(pack_2.Temperature);Serial.println(" °C");
  // Serial.print("Minimum Cell Voltage: ");Serial.print(pack_2.Min_Voltage);Serial.println(" volts");
  // Serial.print("Maximum Cell Voltage: ");Serial.print(pack_2.Max_Voltage);Serial.println(" volts");
  Serial.print("Cell-1 Voltage:       ");Serial.print(pack_2.Cell_Voltage1);Serial.println(" volts");
  Serial.print("Cell-2 Voltage:       ");Serial.print(pack_2.Cell_Voltage2);Serial.println(" volts");
  Serial.print("Cell-3 Voltage:       ");Serial.print(pack_2.Cell_Voltage3);Serial.println(" volts");
  Serial.print("SOC via Voltage:      ");Serial.print(pack_2.Soc_V);Serial.println(" %");
  Serial.print("SOC via Current:      ");Serial.print(pack_2.Soc_C);Serial.println(" %");
}

void pack3() {
  Serial.println("PACK 3:");Serial.print("Slave Address: 0x0");Serial.println(slave_address3,HEX);
  Serial.print("Battery Voltage:      ");Serial.print(pack_3.Bat_Voltage);Serial.println(" volts");
  Serial.print("Battery Current:      ");Serial.print(pack_3.Bat_Current);Serial.println(" mAmps");
  Serial.print("NTC Temperature:      ");Serial.print(pack_3.Temperature);Serial.println(" °C");
  // Serial.print("Minimum Cell Voltage: ");Serial.print(pack_3.Min_Voltage);Serial.println(" volts");
  // Serial.print("Maximum Cell Voltage: ");Serial.print(pack_3.Max_Voltage);Serial.println(" volts");
  Serial.print("Cell-1 Voltage:       ");Serial.print(pack_3.Cell_Voltage1);Serial.println(" volts");
  Serial.print("Cell-2 Voltage:       ");Serial.print(pack_3.Cell_Voltage2);Serial.println(" volts");
  Serial.print("Cell-3 Voltage:       ");Serial.print(pack_3.Cell_Voltage3);Serial.println(" volts");
  Serial.print("SOC via Voltage:      ");Serial.print(pack_3.Soc_V);Serial.println(" %");
  Serial.print("SOC via Current:      ");Serial.print(pack_3.Soc_C);Serial.println(" %");
}

void pack4() {
  Serial.println("PACK 4:");Serial.print("Slave Address: 0x0");Serial.println(slave_address4,HEX);
  Serial.print("Battery Voltage:      ");Serial.print(pack_4.Bat_Voltage);Serial.println(" volts");
  Serial.print("Battery Current:      ");Serial.print(pack_4.Bat_Current);Serial.println(" mAmps");
  Serial.print("NTC Temperature:      ");Serial.print(pack_4.Temperature);Serial.println(" °C");
  // Serial.print("Minimum Cell Voltage: ");Serial.print(pack_4.Min_Voltage);Serial.println(" volts");
  // Serial.print("Maximum Cell Voltage: ");Serial.print(pack_4.Max_Voltage);Serial.println(" volts");
  Serial.print("Cell-1 Voltage:       ");Serial.print(pack_4.Cell_Voltage1);Serial.println(" volts");
  Serial.print("Cell-2 Voltage:       ");Serial.print(pack_4.Cell_Voltage2);Serial.println(" volts");
  Serial.print("Cell-3 Voltage:       ");Serial.print(pack_4.Cell_Voltage3);Serial.println(" volts");
  Serial.print("SOC via Voltage:      ");Serial.print(pack_4.Soc_V);Serial.println(" %");
  Serial.print("SOC via Current:      ");Serial.print(pack_4.Soc_C);Serial.println(" %");
}