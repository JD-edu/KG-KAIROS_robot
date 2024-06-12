const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };

void setup() {
  for(int x=0;x<7;x++) {
  pinMode(led[x], OUTPUT);
  }   
}

void loop() {
  for(int x=0;x<7;x++) {
  
  // led 모두 끄기
  for(int x=0;x<7;x++) {
    digitalWrite(led[x], LOW);
  }
  
  digitalWrite(led[x], HIGH);
  
    delay(1);//1/3.5=0.286Hz
  }
}
