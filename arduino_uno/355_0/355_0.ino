#include <Servo.h>

const int SERVO = 10;
Servo servo;

void setup() {
  servo.attach(SERVO);  
  servo.write(0);

  delay(1000);  

  for(int angle=0;angle<=180;angle++) {
  servo.write(angle);
  delay(30);
  }
  
  servo.detach();
}

void loop() {
  
}   
