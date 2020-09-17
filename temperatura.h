#ifndef temperatura_h
#define temperatura_h
 
#include <Servo.h> 
#include <i2cmaster.h>
#include "arduino.h" ///////////////////////////////////////  

class temperatura{
  public:
  temperatura(){
  }

  temperatura(uint8_t _address){
     address = _address<<1; 
  }

  void setup(){
    i2c_init(); 
    PORTC = (1 << PORTC4) | (1 << PORTC5);
  }
  
  float temperatureCelcius() {
  int dev = address;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);

  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck();       
  data_high = i2c_readAck();      
  pec = i2c_readNak();
  i2c_stop();
  
  double tempFactor = 0.02;
  double tempData = 0x0000; 
  int frac;

  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor)-0.01;
  float celcius = tempData - 273.15;
  
  return celcius;
}

  uint8_t address;


};
#endif
