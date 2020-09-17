#ifndef paquete_h
#define paquete_h

#include "arduino.h"
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class paquete{
  public: 

  paquete(){}

  LiquidCrystal_I2C lcd{0x27,16,2};
  Servo servoMotor;

  void setup(){
    servoMotor.attach(45);
    servoMotor.write(118);
    delay(500);
    lcd.init();
    lcd.backlight();
    pinMode(52, OUTPUT);
    digitalWrite(52, LOW);
  }

  void paqueteDerecha(){    
    servoMotor.write(58);
    delay(1000);
    servoMotor.write (118);
    delay(1000);
  }
  
  void paqueteIzquierda(){
    servoMotor.write (161);
    delay(1000);
    servoMotor.write(118);
    delay(1000);
  }

  void parpadeaLcd(){
    lcd.print("VICTIMA DETECTADA");
    delay(100);

    for(int i = 0; i < 5; i++){
      digitalWrite(52, HIGH);
      delay(500);
      digitalWrite(52, LOW);
      delay(500);
    }

    lcd.clear();
  }

};

#endif
