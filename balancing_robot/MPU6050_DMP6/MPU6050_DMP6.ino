#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {
             // reads the value of the potentiometer (value between 0 and 1023)
       // scale it to use it with the servo (value between 0 and 180)
  myservo.write(90);                  // sets the servo position according to the scaled value
  delay(1000); 
   myservo.write(0);                  // sets the servo position according to the scaled value
  delay(1000);                           // waits for the servo to get there
}