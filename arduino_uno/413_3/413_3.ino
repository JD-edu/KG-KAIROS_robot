#include <TimerOne.h>

const int BUZZER = 10;

const int melody[] = {
  262, 294, 330, 349, 393, 440, 494, 523,  
};

void setup() {
  Timer1.initialize();
  Timer1.pwm(BUZZER, 0);

  Timer1.setPwmDuty(BUZZER, 100);

  for(int note=0;note<8;note++) {
  Timer1.setPeriod(1000000/melody[note]);     
  delay(500);
  }
  
  Timer1.setPwmDuty(BUZZER, 0);
}

void loop() {
  
}
