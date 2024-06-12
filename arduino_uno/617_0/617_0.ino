class NDelayFunc {
  unsigned long t_prev;
  const unsigned long t_delay;
  void (* func)();

public:
  NDelayFunc(
  const unsigned long t_delay,
  void (* func)()) 
  : t_prev(0), t_delay(t_delay), func(func) {}
  
  void run() {
  unsigned long t_now = millis();
  if(t_now - t_prev >= t_delay) {
    t_prev = t_now;

    func();
  }
  }
};

const int LED = 10;
unsigned int t_high = 0;

void fading() {
  t_high++;
  if(t_high>255) t_high = 0;
  analogWrite(LED, t_high);
}

NDelayFunc nDelayFading(4, fading);

void setup() {
  
}

void loop() {
  nDelayFading.run();
}
