#ifndef color_h
#define color_h
#include "arduino.h"
#include "paquete.h"

class color{
  public:
  color(){
    
  }
  
  int s0 = 32 ,s1 = 34, s2 = 28, s3 = 26, s5 = 30,r = 0, g = 0, b = 0; 
  bool blanco = false;
  bool negro = false;

  paquete dispenser;

  void setup(){
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s5, INPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);
  dispenser.setup();
  }
  
  
  void ValoresColores(){
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  r = pulseIn(s5, LOW);
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH); 
  g = pulseIn(s5, LOW); 
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  b = pulseIn(s5, LOW);
  }
  
  void ChecaColor(int r,int g,int b){
    if (r >= 320 && r <= 390 && g >= 190 && g <= 220 && b >= 35 && b <= 70){
    blanco = true;
    negro = false;
    }
    else if (r >= 2500 && r <= 4000 && g >= 400 && g <= 800 && b >= 90 && b <= 300 ){
    negro = true;
    blanco = false;
  }
  }
  
  void imprimeColor (bool blanco, bool negro){
     if (negro == true){
    dispenser.lcd.print ("NEGRO");
    delay(100);
    dispenser.lcd.clear();
    }
    
  }
  

  
  bool colorfinal(){
    ValoresColores();
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.println(" ");
    ChecaColor(r,g,b);
    imprimeColor(blanco,negro);

    if(negro) return false;
    else return false;
  }

};

  #endif
