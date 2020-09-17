#ifndef decisiones_h 
#define decisiones_h

#include "Arduino.h"
#include "movimiento.h"
#include "motores.h"
#include <StackArray.h>

class decisiones{
  public:

  movimiento recorrido;
  motores ruedas{};
  StackArray<char>movPrevios;
  
  decisiones(){
    
  }

  void setup(){
    ruedas.setup();
    recorrido.setup();
  }

  void continuarLaberinto(){
    bool flag = false;
    while(ruedas.EncoderFR._encPos<1950){
      ruedas.forward();
      if(recorrido.temperatureFR.temperatureCelcius() > 30.4 && !flag) {
        ruedas.stopcar();
        recorrido.colores.dispenser.parpadeaLcd(); 
        recorrido.colores.dispenser.paqueteDerecha();
        flag = true;
        }
   //   if(recorrido.temperatureBR.temperatureCelcius() > 35 && !flag) {ruedas.stopcar(); recorrido.colores.dispenser.parpadeaLcd(); flag = true;}
      if(recorrido.temperatureBL.temperatureCelcius() > 30.4 && !flag) {
        ruedas.stopcar(); 
        recorrido.colores.dispenser.parpadeaLcd(); 
        recorrido.colores.dispenser.paqueteIzquierda();
        flag = true;
        }
      if(recorrido.temperatureFL.temperatureCelcius() > 30.4 && !flag) {
        ruedas.stopcar();
        recorrido.colores.dispenser.parpadeaLcd(); 
        recorrido.colores.dispenser.paqueteIzquierda();
        flag = true;
        }
    }
    
    ruedas.stopcar();
    delay(500);

    ruedas.EncoderFR.resetEncPos();
    ruedas.EncoderFL.resetEncPos();
    ruedas.EncoderBR.resetEncPos();
    ruedas.EncoderBL.resetEncPos(); 
    
    movPrevios.push('a');

    recorrido.cambiarCoordenadas();
    recorrido.checarParedes();

    if(!recorrido.isBlack()){
      if(recorrido.posibleDerecha()){
        ruedas.right();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('d');
        movPrevios.push('d');
      }
      else if(recorrido.posibleEnfrente()){
      //continue;
      }
      else if(recorrido.posibleIzquierda()){
        ruedas.left();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('i');
        movPrevios.push('i');
      }
      else{
        regresoPunto();
      }
    }
   else{
    ruedas.minireverse();
    ruedas.stopcar();
    delay(500);
    movPrevios.pop();

    recorrido.cambiarCoordenadasReversa();

    if(recorrido.posibleDerecha()){
        ruedas.right();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('d');
        movPrevios.push('d');
      }
      else if(recorrido.posibleIzquierda()){
        ruedas.left();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('i');
        movPrevios.push('i');
      }
      else{
        regresoPunto();
      }
   }
  }

  void regresoPunto(){
    while(!movPrevios.isEmpty()){
      if(movPrevios.peek() == 'a'){
        ruedas.minireverse();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarCoordenadasReversa();
      }
      else if(movPrevios.peek() == 'd'){
        ruedas.left();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('i');
      }
      else{
        ruedas.right();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('d');
      }

      movPrevios.pop();

       if(recorrido.posibleDerecha()){
        ruedas.right();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('d');
        movPrevios.push('d');
        break;
      }
      else if(recorrido.posibleEnfrente()){
      //continue;
      break;
      }
      else if(recorrido.posibleIzquierda()){
        ruedas.left();
        ruedas.stopcar();
        delay(500);
        recorrido.cambiarDireccion('i');
        movPrevios.push('i');
        break;
      }
    }

    if(movPrevios.isEmpty()) terminarRonda();
  }

  void terminarRonda(){
    recorrido.colores.dispenser.lcd.print("FIN DE RONDA");
    while(true){
      delay(8000);
    }
  }
};

#endif
