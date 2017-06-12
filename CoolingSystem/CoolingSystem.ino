#include "TempSensor.h"
#include "CoolingElement.h"

const int CoolingElementPin = 6; // Pin connected to the peltierelement
const int TempSensorPin = A0; // Pin connected to the NTC

const int SetTemperature = 10; // Desired temprature || We still need to translate the NTC values to temprature.
double CurrentTemperature = 0;

CoolingElement Cooling(CoolingElementPin);
TempSensor Temp(TempSensorPin);

void setup()
{
}

void loop()
{
  CurrentTemperature = Temp.GetTemperatureValue();
  if (CurrentTemperature >= SetTemperature)   // nu puur de ntc waarde. Deze is hoger hoe kouder het is.
  {
    Cooling.Off();
  }
  else
  {
    Cooling.On();
  }
  delay(100);
}

