#include <MCP2515.h>
#include "TempSensor.h"
#include "CoolingElement.h"
#include "iCommunicate.hpp"

const int CoolingElementPin = 6; // Pin connected to the peltierelement
const int TempSensorPin = A0; // Pin connected to the NTC

int8_t SetTemperature = -2; // Desired temprature in graden C
int8_t CurrentTemperature = 0;
CANMSG msg;

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
  else{ Serial.println("Succes");}
  communication.SetCallback(GetMessage);
}

void loop()
{
	communication.Read();
  CurrentTemperature = Temp.GetTemperatureValue();
  Serial.print(CurrentTemperature);
  Serial.print("\t");
  Serial.println(SetTemperature);
  if (CurrentTemperature < SetTemperature)   
  {
    Cooling.Off();
  }  
  else
  {
    Cooling.On();
  }
  delay(100);
  SendMsg();
}

// Gets called when message is recieved, msg.data contains the data.
void GetMessage(CANMSG msg) {
  for (uint8_t i = 0; i < msg.dataLength; i++) {
    Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);
	if(msg.adrsValue == 0x11)
	{
		SetTemperature = msg.data[0];
	}
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

  if (communication.Write(msg)) {
    Serial.println("Wrote msg");
  }
  else {
    Serial.println("Writing went wrong");
  }
}
