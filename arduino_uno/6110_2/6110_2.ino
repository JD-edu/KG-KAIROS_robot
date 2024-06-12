#include "NDelayFunc.h"

const int blink_LED = 13;
unsigned int on_off = 0;

const int fading_LED = 10;
unsigned int t_high = 0;

void blink() {
  on_off++;
  if(on_off>1) on_off = 0;
  digitalWrite(blink_LED, on_off);
}

void fading() {
  t_high++;
  if(t_high>255) t_high = 0;
  analogWrite(fading_LED, t_high);
}

NDelayFunc nDelayBlink(500, blink);
NDelayFunc nDelayFading(4, fading);

void setup() {
  pinMode(blink_LED, OUTPUT);
}

void loop() {
  nDelayBlink.run();
  nDelayFading.run();
}
