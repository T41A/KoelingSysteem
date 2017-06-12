#include "CoolingElement.h"

CoolingElement::CoolingElement(int pin)
{
  elementPin = pin;
  pinMode(elementPin, OUTPUT);
}

void CoolingElement::On(void)
{
  digitalWrite(elementPin, HIGH);
}

void CoolingElement::Off(void)
{
  digitalWrite(elementPin, LOW);
}
