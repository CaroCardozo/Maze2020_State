#ifndef movimiento_h
#define movimiento_h

#include "Arduino.h"
#include "cuadro.h"
#include "ultrasonico.h"
#include "color.h"
#include "temperatura.h"

class movimiento{

  public:

  cuadro tile[15][15];
  ultrasonico ultraFrente{29};
  ultrasonico ultraDerecha{35};
  ultrasonico ultraIzquierda{25};
  ultrasonico ultraAtras{41};
  color colores;
  temperatura temperatureFR{0x5A};
  temperatura temperatureFL{0x5C};
  temperatura temperatureBR{0x5E};
  temperatura temperatureBL{0x5B};
  
  movimiento(){
    
  }

  void setup(){
    colores.setup();
    temperatureFR.setup();
    temperatureFL.setup();
    temperatureBR.setup();
    temperatureBL.setup();
    checarParedes();
    tile[x][y].visitado = true;
    tile[x][y].paredS = ultraAtras.getDistance();
  }
  
  void checarParedes(){
    switch(direccion){
      case 'n':{
        tile[x][y].paredN = ultraFrente.getDistance();
        tile[x][y].paredE = ultraDerecha.getDistance();
        tile[x][y].paredO = ultraIzquierda.getDistance();
      } break;
      case 'e':{
        tile[x][y].paredE = ultraFrente.getDistance();
        tile[x][y].paredS = ultraDerecha.getDistance();
        tile[x][y].paredN = ultraIzquierda.getDistance();
      } break;
      case 'o':{
        tile[x][y].paredO = ultraFrente.getDistance();
        tile[x][y].paredN = ultraDerecha.getDistance();
        tile[x][y].paredS = ultraIzquierda.getDistance();
      }break;
      case 's':{
        tile[x][y].paredS = ultraFrente.getDistance();
        tile[x][y].paredO = ultraDerecha.getDistance();
        tile[x][y].paredE = ultraIzquierda.getDistance();
      }break;
    }
  }

  bool posibleDerecha(){
    switch(direccion){
      case 'n':return (!tile[x][y].paredE && !tile[x+1][y].visitado);
      break;
      case 'e':return (!tile[x][y].paredS && !tile[x][y+1].visitado);
      break;
      case 'o':return (!tile[x][y].paredN && !tile[x][y-1].visitado);
      break;
      case 's':return (!tile[x][y].paredO && !tile[x-1][y].visitado);
      break;
    }
  }

  bool posibleEnfrente(){
    switch(direccion){
      case 'n':return (!tile[x][y].paredN && !tile[x][y-1].visitado);
      break;
      case 'e':return (!tile[x][y].paredE && !tile[x+1][y].visitado);
      break;
      case 'o':return (!tile[x][y].paredO && !tile[x-1][y].visitado);
      break;
      case 's':return (!tile[x][y].paredS && !tile[x][y+1].visitado);
      break;
    }
  }

  bool posibleIzquierda(){
    switch(direccion){
      case 'n':return (!tile[x][y].paredO && !tile[x-1][y].visitado);
      break;
      case 'e':return (!tile[x][y].paredN && !tile[x][y-1].visitado);
      break;
      case 'o':return (!tile[x][y].paredS && !tile[x][y+1].visitado);
      break;
      case 's':return (!tile[x][y].paredE && !tile[x+1][y].visitado);
      break;
    }
  }

  bool posibleAtras(){
    return ultraAtras.getDistance();
  }

  bool posibleEnfrenteReversa(){
    return ultraFrente.getDistance();
  }

  void cambiarCoordenadas(){
    switch(direccion){
      case 'n': y-=1;
      break;
      case 'e': x+=1;
      break;
      case 'o': x-=1;
      break;
      case 's': y+=1;
      break;
    }

    tile[x][y].visitado = true;
  }

  void cambiarCoordenadasReversa(){
    switch(direccion){
      case 'n': y++;
      break;
      case 'e': x--;
      break;
      case 'o': x++;
      break;
      case 's': y--;
      break;
    }
  }

  void cambiarDireccion(char vuelta){
    if(vuelta == 'd'){
      switch(direccion){
        case 'n': direccion = 'e';
        break;
        case 'e': direccion = 's';
        break;
        case 'o': direccion = 'n';
        break;
        case 's': direccion = 'o';
        break;
      }
    }
    else{
      switch(direccion){
        case 'n': direccion = 'o';
        break;
        case 'e': direccion = 'n';
        break;
        case 'o': direccion = 's';
        break;
        case 's': direccion = 'e';
        break;
      }
    }
  }

  bool isBlack(){
    return colores.colorfinal();
  }
  
  int x = 7, y = 7;
  char direccion = 'n';
};

#endif
