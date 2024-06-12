const unsigned int led[12] = { 8, 7, 6, 5, 4, 3, 2, 18, 17, 16, 15, 14 };
void setup() {
  for(int x=0;x<=11;x++) {
  pinMode(led[x], OUTPUT);
  }
}

void loop() {
  for(int x=0;x<=11;x++) {
  
  // led 모두 끄기
  for(int x=0;x<=11;x++) {
    digitalWrite(led[x], LOW);
  }
  
  digitalWrite(led[x], HIGH);
  
  delay(1);//1/6=0.167Hz
  }
}
