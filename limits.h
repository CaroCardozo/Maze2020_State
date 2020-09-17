#ifndef limits_h
#define limits_h
#include "Arduino.h"
class limits{
  public:

  limits(){

  }
  
  limits(int pin){
    _pin = pin;  
  }

  void setup(){
    pinMode(_pin,INPUT_PULLUP);
  }
  
  bool getStatus(){
    return digitalRead(_pin);
  }
  
  int _pin;
};


#endif

