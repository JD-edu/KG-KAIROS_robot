unsigned long t1_prev = 0;
const unsigned long t1_delay = 1000;

unsigned long t2_prev = 0;
const unsigned long t2_delay = 500;

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long t1_now = millis();
  if(t1_now - t1_prev >= t1_delay) {
  t1_prev = t1_now;
  
  Serial.println("t1");
  }

  unsigned long t2_now = millis();
  if(t2_now - t2_prev >= t2_delay) {
  t2_prev = t2_now;
  
  Serial.println("\tt2");
  }
}
