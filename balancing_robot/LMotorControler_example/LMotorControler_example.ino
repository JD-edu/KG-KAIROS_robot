/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/
#include "LMotorController.h"

#define MIN_ABS_SPEED 20

//MOTOR CONTROLLER
int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENB = 10;

LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start...");

}

void loop() {
  // put your main code here, to run repeatedly:
  motorController.move(200);
  Serial.println("move");
  delay(1000);

  motorController.stopMoving();  
  Serial.println("stop");
  delay(1000);

  motorController.move(-200);  
  Serial.println("move back");
  delay(1000);

  motorController.turnLeft(200, false);  
  Serial.println("turn left");
  delay(1000);

}
