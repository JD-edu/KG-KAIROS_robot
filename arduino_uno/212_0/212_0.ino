void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

const int pins[4] = {3, 5, 7, 9};
int i = 0;
void loop() {
  i++;  // 파이썬의 i += 1
  if(i>3){
    i = 0;
  }
  digitalWrite(pins[i], HIGH)
  delay(100);
  digitalWrite(pins[i], LOW)
  
}
