
#include "globals.h"

void turnOnDevice(const int pppin, const float ddduration){
  digitalWrite(pppin, HIGH);
  delay(ddduration * gl_time_multiplier * 1000);

  digitalWrite(pppin, LOW);
}