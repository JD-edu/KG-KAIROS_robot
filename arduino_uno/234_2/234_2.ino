const unsigned int led[12] = { 8, 7, 6, 5, 4, 3, 2, 18, 17, 16, 15, 14 };

void setup() {
  // led 초기화
  for(int x=0;x<=11;x++) {
  pinMode(led[x], OUTPUT);
  }
}

void loop() {
  // led 켜기
  for(int x=0;x<=11;x++) {
  digitalWrite(led[x], HIGH);
  }
  delay(500);

  // led 끄기
  for(int x=0;x<=11;x++) {
  digitalWrite(led[x], LOW);
  }
  delay(500);
}
