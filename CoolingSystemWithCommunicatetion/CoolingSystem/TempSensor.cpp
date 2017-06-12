#include "TempSensor.h"

TempSensor::TempSensor(int pin)
{
  TempSensorPin = pin;
}

int TempSensor::GetTemperatureValue()
{
  double temp = analogRead(TempSensorPin);
  temp = temp *43;
  temp -= 10320;
  temp = temp/530;
  return temp;
}
