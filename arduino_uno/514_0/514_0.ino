const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };

void setup() {
  // led 초기화
  for(int x=0;x<7;x++) {
  pinMode(led[x], OUTPUT);
  }

  // led 켜기
  for(int x=0;x<7;x++) {
  digitalWrite(led[x], HIGH);
  }  
}

void loop() {
  
}
