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
#include <ESP32Servo.h>
#include "BluetoothSerial.h"

#define SERVO1  26
#define SERVO2  27

Servo myservo1, myservo2, myservo3, myservo4;
BluetoothSerial SerialBT;

void servo_center(){
  myservo1.write(90);
  myservo2.write(90);
  
}

void setup() {
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  myservo1.setPeriodHertz(50);    // standard 50 hz servo
  myservo1.attach(SERVO1, 500, 2400);
  myservo2.setPeriodHertz(50); 
  myservo2.attach(SERVO2, 500, 2400);
  SerialBT.begin("KAIROS 1"); //Bluetooth device name
  Serial.begin(115200);
}

int angle1 = 90;
int angle2 = 90;

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    if(c == 'a'){
      Serial.println(c);
      myservo1.write(120);
    }else if(c =='w'){
      Serial.println(c);
      myservo1.write(90);
    }
  }
}
