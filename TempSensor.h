#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
class TempSensor
{
public:
  TempSensor(int Pin);
  int GetTemperatureValue(void);
private:
  int TempSensorPin;

};

#endif
