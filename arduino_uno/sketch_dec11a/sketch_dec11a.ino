#include<Servo.h>

Servo base;

void setup() {
  Serial.begin(115200);
  base.attach(2);
  base.write(0);
}

void loop() {
  if(Serial.available()>0){
    String a = Serial.readStringUntil('\n');
    
    Serial.println(a);
    base.write(a);
    delay(10);
  }
}
