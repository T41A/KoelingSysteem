#include "TempSensor.h"
#include "CoolingElement.h"
#include "iCommunicatie.hpp"

const int CoolingElementPin = 6; // Pin connected to the peltierelement
const int TempSensorPin = A0; // Pin connected to the NTC

const int SetTemperature = 500; // Desired temprature || We still need to translate the NTC values to temprature.
double CurrentTemperature = 0;

CoolingElement Cooling(CoolingElementPin);
TempSensor Temp(TempSensorPin);
iCommunicatie communication;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  if (!communication.Init())
  {
    Serial.println("Setting up CAN failed");
  }
  communication.SetCallback(GetMessage);
}

void loop()
{
  CurrentTemperature = Temp.GetTemperatureValue();
  if (CurrentTemperature >= SetTemperature)   // nu puur de ntc waarde. Deze is hoger hoe kouder het is.
  {
    Cooling.Off();
  }  else
  {
    Cooling.On();
  }
  delay(100);
}

// Gets called when message is recieved, msg.data contains the data.
void GetMessage(CANMSG msg) {
  for (uint8_t i = 0; i < msg.dataLength; i++) {
    Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);
  }
}

void SendMsg() {
  msg.adrsValue = 0x80;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;
  msg.data[0] = CurrentTemperature;
  msg.data[1] = 0;
  msg.data[2] = 0;
  msg.data[3] = 0;
  msg.data[4] = 0;
  msg.data[5] = 0;
  msg.data[6] = 0;
  msg.data[7] = 0;

  if (_com.Write(msg)) {
    Serial.println("Wrote msg");
  }
  else {
    Serial.println("Writing went wrong");
  }
}
