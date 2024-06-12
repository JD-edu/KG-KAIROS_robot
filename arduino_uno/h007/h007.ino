#include <SoftwareSerial.h>

#define blueTX 2   
#define blueRX 3
char ser = 0;
char ble = 0;

SoftwareSerial HC06(blueTX, blueRX);

void setup(){
   Serial.begin(9600);
   HC06.begin(9600);
}

void HC06proc(){
  if(Serial.available()>0){
    ser = Serial.read();
    HC06.write(ser);
  }
  if(HC06.available()>0){
    ble = HC06.read();
    Serial.write(ble);
  }
}

void loop(){
  HC06proc();
}
