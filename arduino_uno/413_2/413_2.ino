#include <TimerOne.h>

const int BUZZER = 10;

void setup() {
  Timer1.initialize();
  Timer1.pwm(BUZZER, 0);

  Timer1.setPwmDuty(BUZZER, 100);

  for(int cnt=0;cnt<=2;cnt++) {
  Timer1.setPeriod(1000000/262);  
  delay(1000);
  Timer1.setPeriod(1000000/294);  
  delay(1000);
  }
  
  Timer1.setPwmDuty(BUZZER, 0);
}

void loop() {
  
}
