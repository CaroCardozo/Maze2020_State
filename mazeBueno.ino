#include "decisiones.h"

decisiones robot;

void sumarEncoderPosition(){
  robot.ruedas.EncoderFR._encPos++;
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(19), sumarEncoderPosition, CHANGE); 
  robot.setup();
}

void loop() {
  robot.continuarLaberinto();
}
