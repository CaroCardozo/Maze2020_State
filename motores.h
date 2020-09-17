#ifndef motores_h
#define motores_h
#include "Arduino.h"
#include "limits.h"
#include "encoders.h"
#include <Adafruit_BNO055.h>
#define BNO055_SAMPLERATE_DELAY_MS 10

class motores{
 public:
  /* ENCODER DELCARATION */
  encoders EncoderFL{7,8,3,50};
  encoders EncoderFR{5,6,19,52};
  encoders EncoderBR{12,11,18,48};
  encoders EncoderBL{10,9,2,46};
  Adafruit_BNO055 bno;

  motores(){
  }

  void setup(){
    limitDA.setup();
    limitIA.setup();
    limitDF.setup();
    limitIF.setup();
    EncoderFL.setup();
    EncoderFR.setup();
    EncoderBL.setup();
    EncoderBR.setup();
    bno.begin();
    bno.setExtCrystalUse(true);
    delay(4000);
    sensors_event_t event;
    bno.getEvent(&event);
  }
  
  void forward(){
    EncoderFR.forward(Velocidad);
    EncoderFL.forward(Velocidad);
    EncoderBR.forward(Velocidad);
    EncoderBL.forward(Velocidad);
  }

  void reverseEnReversa(){
    iCont = 0;
    statusf1 = limitDF.getStatus();
    statusf2 = limitIF.getStatus();
    while((statusf1 == HIGH) || (statusf2 == HIGH)){
      statusf1 = limitDF.getStatus();
      statusf2 = limitIF.getStatus();
      EncoderFR.forward(Velocidad);
      EncoderFL.forward(Velocidad);
      EncoderBR.forward(Velocidad);
      EncoderBL.forward(Velocidad);
      iCont++;
      delay(1);
      if(iCont >= 5000)
      break;
    }

    delay(500);

    stopcar();
    delay(500);

    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos();
  }
  
  void reverse(){
    iCont = 0;
    statusb1 = limitDA.getStatus();
    statusb2 = limitIA.getStatus();
    while((statusb1 == HIGH) || (statusb2 == HIGH)){
      statusb1 = limitDA.getStatus();
      statusb2 = limitIA.getStatus();
      EncoderFR.backward(Velocidad);
      EncoderFL.backward(Velocidad);
      EncoderBR.backward(Velocidad);
      EncoderBL.backward(Velocidad);
      iCont++;
      delay(1);
      if(iCont >= 5000)
      break;
    }

    delay(500);

    stopcar();
    delay(500);

    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos();
  }
  
  void right(){
    double anguloActual = -1;
    double anguloDeseAdo = nuevoSetPoint() + 90;
    if(anguloDeseAdo > 360) anguloDeseAdo -= 360;
  
  while(anguloActual < anguloDeseAdo - 6){
   
    EncoderFR.backward(140);
      EncoderFL.forward(140);
      EncoderBR.backward(140);
      EncoderBL.forward(140); 
    
    (nuevoSetPoint() > anguloDeseAdo + 6) ? anguloActual = nuevoSetPoint () - 360 : anguloActual = nuevoSetPoint();
  }
  
    endMove();
    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos();
  }
  
  void left(){
    double anguloActual = 361;
    double anguloDeseAdo = nuevoSetPoint() - 90;
    if(anguloDeseAdo < 0) anguloDeseAdo += 360;
    
    while(anguloActual > anguloDeseAdo + 6){
   
    EncoderFR.forward(140);
      EncoderFL.backward(140);
      EncoderBR.forward(140);
      EncoderBL.backward(140); 
    
    (nuevoSetPoint() < anguloDeseAdo - 6) ? anguloActual = nuevoSetPoint () + 360 : anguloActual = nuevoSetPoint();
  }
  
    endMove();  
    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos(); 
  }
  
  void stopcar(){
    EncoderFR.completeStop();
    EncoderFL.completeStop();
    EncoderBR.completeStop();
    EncoderBL.completeStop();  
    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos(); 
  }
  
  void minireverse(){
    while(EncoderFR._encPos<1950){
      EncoderFR.backward(Velocidad);
      EncoderFL.backward(Velocidad);
      EncoderBR.backward(Velocidad);
      EncoderBL.backward(Velocidad);
    }
    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos(); 
  }

  void acomodoPatras(){
    EncoderFR.backward(Velocidad);
      EncoderFL.backward(Velocidad);
      EncoderBR.backward(Velocidad);
      EncoderBL.backward(Velocidad);
  }
  
  void endMove(){
    EncoderFR.completeStop();
    EncoderFL.completeStop();
    EncoderBR.completeStop();
    EncoderBL.completeStop();  
    EncoderFR.resetEncPos();
    EncoderFL.resetEncPos();
    EncoderBR.resetEncPos();
    EncoderBL.resetEncPos(); 
  }

  double nuevoSetPoint() {
  sensors_event_t event;
  bno.getEvent(&event);

  return event.orientation.x;
}
  
  limits limitDF{44},limitDA{50},limitIF{46},limitIA{48};
  int statusf1, statusf2, statusb1, statusb2, iCont, giro;
   int CONT = 920;
   int Velocidadgiro = 210;
   int Velocidadgiro1 = 210;
   int Velocidad = 150;
};

#endif

