#include <Servo.h>

const int SERVO = 10;
Servo servo;
const int buttonPin = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  servo.attach(SERVO);
  servo.write(0);
  delay(1000);    
}

void loop() {
  int buttonInput = digitalRead(buttonPin);
  
  if(buttonInput==1) servo.write(150);
  else servo.write(30);
}
