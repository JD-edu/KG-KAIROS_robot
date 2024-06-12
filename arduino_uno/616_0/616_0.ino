const int t1_LED = 13;
unsigned int on_off = 0;

const int t2_LED = 10;
unsigned int t_high = 0;

unsigned long t1_prev = 0;
const unsigned long t1_delay = 500;

unsigned long t2_prev = 0;
const unsigned long t2_delay = 4;

void setup() {
  pinMode(t1_LED, OUTPUT);
}

void loop() {
  unsigned long t1_now = millis();
  if(t1_now - t1_prev >= t1_delay) {
  t1_prev = t1_now;

  on_off++;
  if(on_off>1) on_off = 0;
  digitalWrite(t1_LED, on_off);
  }

  unsigned long t2_now = millis();
  if(t2_now - t2_prev >= t2_delay) {
  t2_prev = t2_now;

  t_high++;
  if(t_high>255) t_high = 0;
  analogWrite(t2_LED, t_high);
  }
}
