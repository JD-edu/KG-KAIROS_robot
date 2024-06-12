#include <SoftwareSerial.h>
SoftwareSerial BT(7, 8);

void forward1() {
  analogWrite(3, 0); //
  analogWrite(5, 150); 
  analogWrite(6, 150);
  analogWrite(9, 0); //
}
void backward1() {
  analogWrite(3, 150);
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 150);
}
void turnleft() {
  analogWrite(3, 150);
  analogWrite(5, 0);
  analogWrite(6, 150);
  analogWrite(9, 0);
}
void turnright() {
  analogWrite(3, 0);
  analogWrite(5, 150);
  analogWrite(6, 0);
  analogWrite(9, 150);
}

void stopall() {
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
}

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  BT.begin(9600);
}

void loop() { 
  if (BT.available()) {
    char c = BT.read();
    if (c == 'f')forward1();
    if (c == 'b')backward1();
    if (c == 'l')turnleft();
    if (c == 'r')turnright();
    if (c == 's')stopall();
  }
}
