#include <SoftwareSerial.h>

SoftwareSerial HC06(7,8); 

int trig = 12;
int echo = 13;

int leftSpeed = 10;         
int leftWheel = 9;
int rightSpeed = 6;         
int rightWheel = 5;
int speed = 127;            

void setup() {
  Serial.begin(9600);      
  HC06.begin(9600);         
  pinMode(leftSpeed,OUTPUT);
  pinMode(leftWheel,OUTPUT);
  pinMode(rightSpeed,OUTPUT);
  pinMode(rightWheel,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  RC_control('s');
}

void loop() {
  if(Serial.available()) {
    char ser = Serial.read();
    HC06.write(ser);
    RC_control(ser);
  } 

  if(HC06.available())  {
    char ble = HC06.read();
    Serial.write(ble);
    RC_control(ble);
  }
  long hc  = pulseIn(echo,HIGH)/58.2; 
  hcsr04_check(hc);
}

void RC_control(char com){
  switch(com) {
    case 's' : 
    case 'S' : 
          digitalWrite(leftWheel, LOW);
          digitalWrite(rightWheel, LOW);
          analogWrite(leftSpeed,0);
          analogWrite(rightSpeed,0);
          break;
          
    case 'f' :
    case 'F' :
          digitalWrite(leftWheel, LOW);
          analogWrite(leftSpeed, speed);
          digitalWrite(rightWheel, LOW);
          analogWrite(rightSpeed, speed);
          break;
          
    case 'b' :
    case 'B' :
          digitalWrite(leftWheel, HIGH);
          analogWrite(leftSpeed, 255-speed);
          digitalWrite(rightWheel, HIGH);
          analogWrite(rightSpeed, 255-speed);
          break;

    case 'r' :
    case 'R' :
          digitalWrite(leftWheel, HIGH);
          analogWrite(leftSpeed, 255-speed);
          digitalWrite(rightWheel, LOW);
          analogWrite(rightSpeed, speed);
          break;

    case 'l' :
    case 'L' :
          digitalWrite(leftWheel, LOW);
          analogWrite(leftSpeed, speed);
          digitalWrite(rightWheel, HIGH);
          analogWrite(rightSpeed, 255-speed);
          break;
  }             
}

void hcsr04_check(long hc){    
    Serial.print(hc);
    Serial.println("cm");
    delay(100);
}
