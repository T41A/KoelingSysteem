#ifndef COOLINGELEMENT_H
#define COOLINGELEMENT_H
#include <arduino.h>
class CoolingElement
{
public:
  CoolingElement(int pin);
  void On(void);
  void Off(void);
private:
  int elementPin;
};

#endif
