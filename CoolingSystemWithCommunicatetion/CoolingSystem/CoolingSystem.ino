#include <MCP2515.h>
#include "TempSensor.h"
#include "CoolingElement.h"
#include "iCommunicate.hpp"

const int CoolingElementPin = 6; // Pin connected to the peltierelement
const int TempSensorPin = A0; // Pin connected to the NTC

int8_t SetTemperature = 15; // Desired temprature in graden C
int8_t CurrentTemperature = 0;
CANMSG msg;

unsigned long previousMillis = 0;
const long interval = 1000;

CoolingElement Cooling(CoolingElementPin);
TempSensor Temp(TempSensorPin);
iCommunicate communication;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  if (!communication.Init())
  {
    Serial.println("Setting up CAN failed");
  }
  else {
    Serial.println("Succes");
  }
  communication.SetCallback(GetMessage);
}

void loop()
{
  communication.Read();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    int PreviousTemperature = CurrentTemperature;
    CurrentTemperature = Temp.GetTemperatureValue();
    if (CurrentTemperature <= SetTemperature)
    {
      Cooling.Off();
    }
    else
    {
      Cooling.On();
    }
    if (PreviousTemperature != CurrentTemperature)
    {
      SendMsg();
    Serial.print(CurrentTemperature);
    Serial.print("\t");
    Serial.println(SetTemperature);
    }
  }
}

// Gets called when message is recieved, msg.data contains the data.
void GetMessage(CANMSG msg) {
  Serial.print("msg.id");
  Serial.println(msg.adrsValue, HEX);
  for (uint8_t i = 0; i < msg.dataLength; i++) {
    Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);
    if (msg.adrsValue == 0x11)
    {
    SetTemperature = msg.data[0];
    }
  }
}

void SendMsg() {
  msg.adrsValue = 0x80;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 1;
  msg.data[0] = CurrentTemperature;

  if (communication.Write(msg)) {
    Serial.println("Wrote msg");
  }
  else {
    Serial.println("Writing went wrong");
  }
}
