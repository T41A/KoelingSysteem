#include "TempSensor.h"
#include "CoolingElement.h"

int coolingElement = 0; // vervang 0 door de pin waar het koolelement op is aangesloten
int tempSensor = 0; // vervang 0 door de pin waar de temperatuur sensor op is aangesloten

int temperature = 0; // de temperatuur van de kooling die we meten
int setTemperature = 0; // de temperatuur die we willen dat de kooling heeft

void setup()
{
  pinMode(coolingElement, INPUT);
  pinMode(tempSensor, OUTPUT);

  CoolingElement(coolingElement);
  TempSensor(tempSensor);
}

void loop()
{
  temperature = GetTemperatureValue();

  if(temperature <= setTemperature)
  {
    Off();
  }
  else
  {
    On();
  }
}
