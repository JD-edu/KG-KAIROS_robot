const unsigned int led[6] = { 3, 5, 6, 9, 10, 11 };

void setup() {
  
}

void loop() {
  for(int n=0;n<=5;n++) {
  
    for(int t_high=0;t_high<=255;t_high++) {
      analogWrite(led[n], t_high);
      delay(2);
    }
    analogWrite(led[n], 0);
  }
}
