const int ACTIVE_BUZZER = 10;

void setup() {
  pinMode(ACTIVE_BUZZER, OUTPUT);

  for(int cnt=0;cnt<=2;cnt++) {
  digitalWrite(ACTIVE_BUZZER, HIGH);
  delay(1000);  
  digitalWrite(ACTIVE_BUZZER, LOW);
  delay(1000);  
  }
}

void loop() {
  
}
