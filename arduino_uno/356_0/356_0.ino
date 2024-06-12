#include <Servo.h>

const int SERVO = 10;
Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(SERVO);
  servo.write(0);
  delay(1000);    
}

void loop() {
  if(Serial.available()) {
  char userInput = Serial.read();
  
  switch(userInput) {
    case '1':
    servo.write(30);
    delay(1000);
    break;
    case '2':
    servo.write(90);
    delay(1000);
    break;
    case '3':
    servo.write(150);
    delay(1000);
    break;
    default:
    break;
  }
  }  
}
