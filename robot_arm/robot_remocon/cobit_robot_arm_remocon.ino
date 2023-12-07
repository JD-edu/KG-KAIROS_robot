#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
command code(1 byte) - payload (0 byte ~ 8byte) 
0x04: Program robot 
*/

#define CMD_RUN_ROBOT         0x01
#define CMD_SAVE_POS          0x02
#define CMD_RESET_ROBOT       0x03
#define CMD_MOVE_ROBOT_JOY    0x04
#define CMD_CLEAR_POS         0x05
#define CMD_MOVE_ROBOT_SERIAL 0x06
#define CMD_MOVE_ROBOT_6LINK  0x07
#define CMD_STOP_ROBOT        0x08

RF24 radio(7, 8);
const byte address = '1'; 

unsigned char inputPin[6] = { A0, A1, A2, A3, A4, A5};
char packet[13] = {0,};
int joystick1 = 0, joystick2 = 0, joystick3 = 0, joystick4 = 0, joystick5 = 0, joystick6 = 0 ;
bool joystickFlag = false;

int reset = 0;


void setup() {

  pinMode(4, INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  
 
  Serial.println("co:bit robot arm mk1 remocon start...");
  for(char i = 0;i < 4;i++ ){
    pinMode(inputPin[i], INPUT);
  }
}

void loop() {
  // initialize data packet 
  for(int i = 0;i < 10;i++){
    packet[i] = 0x00;
  }

  // 임시로 구현 ... 리모컨 하드웨어 구현되면 제거
  // 시리얼 포트로 로봇 리셋명령을 보냄. 그러면 로봇 아두이노가 이 명령을 받고 로봇을 리셋한다. 
  /*String inString = "";
  if(Serial.available()){
    inString = Serial.readStringUntil('\n');
    if(inString[0] == '1'){
      packet[0] = CMD_RUN_ROBOT;
      radio.write( &packet, 13 );
    }else if(inString[0] == '2'){
      packet[0] = CMD_SAVE_POS;
      radio.write( &packet, 13 );
    }else if(inString[0] == '3'){
      packet[0] = CMD_RESET_ROBOT;
      radio.write( &packet, 13 );
    }else if(inString[0] == '8'){
      Serial.println("");
      packet[0] = CMD_STOP_ROBOT;
      radio.write( &packet, 13 );
    }
  }*/
  reset = digitalRead(4);
  Serial.println(reset);
 

  // get joystick position 
  joystick1 = analogRead(A0);
  joystick2 = analogRead(A1);
  joystick3 = analogRead(A2);
  joystick4 = analogRead(A3);
  joystick5 = analogRead(A4);
  joystick6 = analogRead(A5);

  // if each joystick is up/down position, 
  if(joystick1 < 200  || joystick1 > 800){
    joystickFlag = true;
  }else if(joystick2 < 200  || joystick2 > 800){
    joystickFlag = true;
  }else if(joystick3 < 200  || joystick3 > 800){
    joystickFlag = true;
  }else if(joystick4 < 200  || joystick4 > 800){
    joystickFlag = true;
  }else if(joystick5 < 200  || joystick5 > 800){
    joystickFlag = true;
  }else if(joystick6 < 200  || joystick6 > 800){
    joystickFlag = true;
  }else{
    joystickFlag = false;
  }
  if(joystickFlag == true){
    packet[0]= CMD_MOVE_ROBOT_JOY;
    packet[1]=(joystick1 & 0xFF);      
    packet[2]=((joystick1 >> 8) & 0xFF); 
    packet[3]=(joystick2 & 0xFF);      
    packet[4]=((joystick2 >> 8) & 0xFF); 
    packet[5]=(joystick3 & 0xFF);      
    packet[6]=((joystick3 >> 8) & 0xFF); 
    packet[7]=(joystick4 & 0xFF);      
    packet[8]=((joystick4 >> 8) & 0xFF); 
    packet[9]=(joystick5 & 0xFF);      
    packet[10]=((joystick5 >> 8) & 0xFF); 
    packet[11]=(joystick6 & 0xFF);      
    packet[12]=((joystick6 >> 8) & 0xFF); 
    radio.write( &packet, 13 );
  }
  joystickFlag == false;
 
}