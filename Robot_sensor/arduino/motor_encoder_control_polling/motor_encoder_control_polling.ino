/*
MIT License

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

#define ENCA 2 // pin2 of the Arduino
#define ENCB 3 // Pin3 of the Arduino
int ENCA_DATA;
int ENCB_DATA;
 
void setup() {
  Serial.begin(9600); // Activates Serial communication
  pinMode(ENCA,INPUT); // sets pin2 as the input
  pinMode(ENCB,INPUT); // sets pin3 as the input
}
 
void loop() {
  ENCA_DATA = digitalRead(ENCA); 
// We simply read Pin2 of the Arduino and store the result in variable ENCA_DATA
  ENCB_DATA = digitalRead(ENCB); 
// We simply read Pin3 of the Arduino and store the result in variable b
  Serial.print(ENCA_DATA*5); 
  Serial.print(" ");
  Serial.print(ENCB_DATA*5);
  Serial.println();
}