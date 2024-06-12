#include <TimerOne.h>

const int LED = 10;

void setup() {
  Timer1.initialize();
  Timer1.pwm(LED, 0);

  Timer1.setPeriod(1000000/100); //100Hz
  Timer1.setPwmDuty(LED, 511); //0~1023
}

void loop() {
  
}
