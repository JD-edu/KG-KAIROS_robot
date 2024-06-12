const int LED = 13;
int on_off = 0;

unsigned long t_prev = 0;
const unsigned long t_delay = 500;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  unsigned long t_now = millis();
  if(t_now - t_prev >= t_delay) {
  t_prev = t_now;

  on_off++;
  if(on_off>1) on_off = 0;
  digitalWrite(LED, on_off);
  }
}
