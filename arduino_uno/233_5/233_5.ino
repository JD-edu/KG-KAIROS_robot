const unsigned int led[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void setup() {
  for(int x=0;x<=7;x++) {
    pinMode(led[x], OUTPUT);
  }   
}

void loop() {
  for(int x=0;x<=7;x++) {
    for(int x=0;x<=7;x++) {
      digitalWrite(led[x], LOW);
    }
    digitalWrite(led[x], HIGH);
    delay(1); //1/4=0.25Hz
  }
}
