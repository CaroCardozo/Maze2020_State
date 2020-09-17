#ifndef encoders_h
#define encoders_h
#include "Arduino.h"

class encoders{
  public:

    encoders(){
      
    }
  
    encoders(byte pinFwd, byte pinBwd, byte encA, byte encB){
        _pinFwd = pinFwd;
        _pinBwd = pinBwd;
        _encA = encA;
        _encB = encB;
    }

    void setup(){
        pinMode(_pinFwd, OUTPUT);
        pinMode(_pinBwd, OUTPUT);
        pinMode(_encA, INPUT);
        pinMode(_encB, INPUT);
        digitalWrite(_encA, HIGH);
        digitalWrite(_encB, HIGH);
    }
    
    void forward(int velocity){
        analogWrite(_pinFwd, velocity);
        analogWrite(_pinBwd, 0);
    }
    
    void backward(int velocity){
      analogWrite(_pinFwd, 0);
      analogWrite(_pinBwd, velocity);
    }
    
    void completeStop(){
      analogWrite(_pinFwd, 0);
      analogWrite(_pinBwd, 0);
    }
    
    void updateEncPos(){
      if(digitalRead(_encA)){
      _encPos++;
    }
    }
    
    void resetEncPos(){
      _encPos = 0;
    }
    
    int getEncoderA(){
      return _encA;
    }
    
    int getEncPos(){
      return _encA;
    }
    
    int _pinFwd, _pinBwd, _encA, _encB, _encPos = 0;

};

#endif
