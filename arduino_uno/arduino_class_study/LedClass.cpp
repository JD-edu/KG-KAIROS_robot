#include "Arduino.h"
#include "LedClass.h"

LedClass::LedClass(int pin){
  pin_num = pin;
}

void LedClass::begin(){
  pinMode(pin_num, OUTPUT);
}

void LedClass::turn_on(){
  digitalWrite(pin_num, HIGH);
}

void LedClass::turn_off(){
  digitalWrite(pin_num, LOW);
}