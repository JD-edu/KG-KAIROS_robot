const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for(int t_high=0;t_high<=500;t_high++) {
    digitalWrite(LED, HIGH);
    delayMicroseconds(t_high);
    digitalWrite(LED, LOW);
    delayMicroseconds(500-t_high);
  }
}
