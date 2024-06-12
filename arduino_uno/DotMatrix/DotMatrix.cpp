#include "Arduino.h"
#include "DotMatrix.h"

const unsigned int _DotMatrix::pins[1+16] = {
  -1, 10,11,12,13,14,15,16,17, 2,3,4,5,6,7,8,9
};

const unsigned int _DotMatrix::R[1+8] = { -1,R1,R2,R3,R4,R5,R6,R7,R8 };
const unsigned int _DotMatrix::C[1+8] = { -1,C1,C2,C3,C4,C5,C6,C7,C8 };

void _DotMatrix::init() {
  // 도트 매트릭스 핀 초기화
  for(int n=1;n<=8;n++) {
	pinMode(pins[R[n]], OUTPUT);
	pinMode(pins[C[n]], OUTPUT);
  } 
  
  // 도트 매트릭스 끄기 
  for(int n=1;n<=8;n++) {
	digitalWrite(pins[R[n]], HIGH);
	digitalWrite(pins[C[n]], HIGH);
  }
}

void _DotMatrix::draw(const unsigned int image[1+8][1+8]) {
   // 도트 매트릭스 그리기
   static int n = 1;
   n++;
   if(n>8) n = 1;
   
  // 열을 꺼준다.
  if(n>1) digitalWrite(pins[R[n-1]], HIGH);
  if(n==1) digitalWrite(pins[R[8]], HIGH);

  // 행을 켤 준비를 한다.
  for(int m=1;m<=8;m++) {
	if(image[n][m] == 1)
	  digitalWrite(pins[C[m]], HIGH);
	else digitalWrite(pins[C[m]], LOW);
  }
  
  // 열을 켜준다.
  for(int m=1;m<=8;m++) {
	if(image[n][m] == 1) {
	  digitalWrite(pins[R[n]], LOW);
	  break;
	}
  }
}

_DotMatrix DotMatrix;