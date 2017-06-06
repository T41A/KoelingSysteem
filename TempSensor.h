#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
class TempSensor
{
public:
  TempSensor(int Pin);
  int GetTemperatureValue(void); // geeft een temperatuur in tienede van graden Celcius.
private:
  int TempSensorPin;

};

#endif
