const int LED = 10;
int t_high = 0;

unsigned long t_prev = 0;
const unsigned long t_delay = 4;

void setup() {
  
}

void loop() {
  unsigned long t_now = millis();
  if(t_now - t_prev >= t_delay) {
  t_prev = t_now;

  t_high++;
  if(t_high>255) t_high = 0;
  analogWrite(LED, t_high);
  }
}
