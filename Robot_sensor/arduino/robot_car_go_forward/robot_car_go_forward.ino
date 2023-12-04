#include <AFMotor.h>
AF_DCMotor motor1(1); // 우측
AF_DCMotor motor2(3); // 좌측

//오른쪽 바퀴
const byte encoderPinA = 18;//A pin -> the interrupt pin 5, 파란선
const byte encoderPinB = 16;//B pin -> 흰색선(녹)
//왼쪽 바퀴
const byte encoderPinC = 19;//A pin -> the interrupt pin 4, 파란선
const byte encoderPinD = 17;//B pin -> 흰색선(녹)

int encoderPos = 0; // 1920이면 한바퀴
int encoderPosL = 0;
byte encoder0PinALast;
byte encoder0PinALastL;

boolean DirectionL = FORWARD;
boolean Direction = FORWARD;
int standardSpeed = 60;
int fixedSpeed =standardSpeed;


//왼쪽바퀴 스피드 감시
void wheelSpeedL(){  
  int Lstate = digitalRead(encoderPinC);
  if((encoder0PinALastL == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoderPinD);
    if(val == LOW && DirectionL)DirectionL = false; //Reverse
    else if(val == HIGH && !DirectionL)DirectionL = true;  //Forward
  }
  encoder0PinALastL = Lstate;
  
  if(!DirectionL)  encoderPosL++;
  else  encoderPosL--;

  //일정 값 이상 넘어가면 초기화
  if(encoderPosL > 10000)encoderPosL = encoderPosL - 10000;
  else if(encoderPosL < -10000)encoderPosL = encoderPosL + 10000;
}


//오른쪽바퀴 스피드 감시
void wheelSpeedR(){  
  int Lstate = digitalRead(encoderPinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoderPinB);
    if(val == LOW && Direction)Direction = false; //Reverse
    else if(val == HIGH && !Direction)Direction = true;  //Forward
  }
  encoder0PinALast = Lstate;
 
  if(!Direction)  encoderPos++;
  else  encoderPos--;
  
  if(encoderPos > 10000)encoderPos = encoderPos - 10000;
  else if(encoderPos < -10000)encoderPos = encoderPos + 10000;
}


// 초기 실행
void setup() {
  //엔코더 설정
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(5, wheelSpeedR, CHANGE); // 5는 interrupt 핀번호
  
  pinMode(encoderPinD, INPUT_PULLUP);
  attachInterrupt(4, wheelSpeedL, CHANGE); // 4는 interrupt 핀번호
  
  
  Serial.begin(9600);

  motor1.run(FORWARD);
  motor1.setSpeed(standardSpeed);
  motor2.run(FORWARD);
  motor2.setSpeed(standardSpeed);
}


//루프
void loop(){
  float gap = abs(encoderPosL) - abs(encoderPos); // 왼쪽 바퀴와 오른쪽 바퀴 스피드를 비교
  
  if(gap > 10){ // 왼쪽바퀴가 더 빠름
    fixedSpeed = standardSpeed * (100 - abs(gap)/10) / 100; //속도 줄이기
  }
  else if(gap < -10){ // 왼쪽바퀴가 더 느림
    fixedSpeed = standardSpeed * (100 + abs(gap)/10) / 100; //속도 높이기
  }

  //왼쪽바퀴 스피드 수정
  motor2.setSpeed(fixedSpeed); 

  //밑에는 비교
  Serial.print("   encoderPos : ");
  Serial.println(encoderPos);
  Serial.print("   encoderPosL : ");
  Serial.println(encoderPosL);
  Serial.print("   fixedSpeed : ");
  Serial.println(fixedSpeed);
  Serial.println("----------------");
}