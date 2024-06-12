void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long t_now = millis();
  Serial.println(t_now);
}
