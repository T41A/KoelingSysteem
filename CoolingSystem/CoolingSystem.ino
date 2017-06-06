#include "TempSensor.h"
#include "CoolingElement.h"
const int CoolingElementPin = 6; // Pin connected to the peltierelement
const int TempSensorPin = A0; // Pin connected to the NTC
const int SetTemperature = 500; // Desired temprature || We still need to translate the NTC values to temprature.

CoolingElement Cooling(CoolingElementPin);
TempSensor Temp(TempSensorPin);

void setup()
{
}

void loop()
{
  if (Temp.GetTemperatureValue() >= SetTemperature) Cooling.Off(); else Cooling.On();
  delay(100);
}
