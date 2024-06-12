#include <TimerOne.h>

const int SERVO = 10;

const int SERVO_PERIOD = 20000; //us
const int SERVO_MINDUTY = (1024/20)*0.7;//=35
const int SERVO_MAXDUTY = (1024/20)*2.3;//=117

void setup() {
  Timer1.initialize();
  Timer1.pwm(SERVO, 0);

  Timer1.setPeriod(SERVO_PERIOD);
  Timer1.setPwmDuty(SERVO, SERVO_MINDUTY);

  delay(1000);  

  for(int angle=SERVO_MINDUTY;angle<=SERVO_MAXDUTY;angle++) { 
  Timer1.setPwmDuty(SERVO, angle); 
  delay(30);
  }
  
  Timer1.disablePwm(SERVO);
}

void loop() {
  
}   
