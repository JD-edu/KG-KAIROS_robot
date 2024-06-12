const unsigned int led[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void setup() {
  // led 초기화
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(led[5], OUTPUT);
  pinMode(led[6], OUTPUT);
  pinMode(led[7], OUTPUT);

  // led 켜기
  digitalWrite(led[0], HIGH);
  digitalWrite(led[1], HIGH);
  digitalWrite(led[2], HIGH);
  digitalWrite(led[3], HIGH);
  digitalWrite(led[4], HIGH);
  digitalWrite(led[5], HIGH);
  digitalWrite(led[6], HIGH);
  digitalWrite(led[7], HIGH);
}

void loop() {
  
}
