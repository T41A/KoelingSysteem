#include "TempSensor.h"

TempSensor::TempSensor(int pin)
{
  TempSensorPin = pin;
}

int TempSensor::GetTemperatureValue()
{
  return analogRead(TempSensorPin);
  //TODO: Translation of NTC to temprature values.
}
