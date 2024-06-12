const int LED = 10;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(9);
  digitalWrite(LED, LOW);
  delay(1);
}
