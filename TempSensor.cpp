#include "TempSensor.h"

TempSensor::TempSensor(int pin)
{
  TempSensorPin = pin;
}

int GetTemperatureValue()
{
  return analogRead(TempSensorPin);
  // hier moet nog een berekening af de analoge waarde naar een temperatuur
}
