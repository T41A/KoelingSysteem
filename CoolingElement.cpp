#include "CoolingElement.h"

CoolingElement::CoolingElement(int pin)
{
  elementPin = pin;
}

void CoolingElement::On(void)
{
  digitalWrite(elementPin, HIGH);
}

void Off(void)
{
  digitalWrite(elementPin, HIGH);
}
