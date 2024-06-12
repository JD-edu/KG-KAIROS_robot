#include <Servo.h>

const int SERVO = 10;
Servo servo;
const int buttonPin = 2;

int servo_state = 30;
bool servo_state_changed = false;

void buttonPressed() {
  servo_state = (servo_state == 30)?150:30;
  servo_state_changed = true;
}

void setup() {  
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);
  servo.attach(SERVO);  
  servo.write(0);
  delay(1000);
}

void loop() {
  if(servo_state_changed) {
    servo_state_changed = false;
    servo.write(servo_state);
  }   
}
