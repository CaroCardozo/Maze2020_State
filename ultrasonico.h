#ifndef ultrasonico_h
#define ultrasonico_h 

#include "Arduino.h"
#include <NewPing.h>

class ultrasonico{
  public:

  ultrasonico():sonar(0,0){
    
  }
  
  ultrasonico(int pingPin):sonar(pingPin,pingPin){
    maximo = 21;
  }
  
  bool getDistance(){
    unsigned int distance = sonar.ping_cm();
    Serial.println(distance);
    if (distance > maximo || distance == 0){
      return false;
    }
    else{
      return true;
    }
  }
  
  int medirDistancia(){
    unsigned int distance = sonar.ping_cm();
    Serial.println(distance);
    return distance;
  }
  
 NewPing sonar;
  int maximo;
};

#endif
