const int ACTIVE_BUZZER = 10;

void setup() {
  pinMode(ACTIVE_BUZZER, OUTPUT);
  
  digitalWrite(ACTIVE_BUZZER, HIGH);
  delay(3000);  
  digitalWrite(ACTIVE_BUZZER, LOW);
}

void loop() {
  
}
