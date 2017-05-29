#include "TempSensor.h"

TempSensor::TempSensor(int pin)
{
  TempSensorPin = pin;
}

int GetTemperatureValue()
{
  return analogRead(TempSensorPin);
}
