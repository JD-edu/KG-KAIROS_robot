const unsigned int led[6] = { 3, 5, 6, 9, 10, 11 };

void setup() {
  
}

void loop() {
  
  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[0], t_high);
    delay(2);
  }
  
  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[1], t_high);
    delay(2);
  }
  
  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[2], t_high);
    delay(2);
  }
  
  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[3], t_high);
    delay(2);
  }

  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[4], t_high);
    delay(2);
  } 
  
  for(int t_high=0;t_high<=255;t_high++) {
    analogWrite(led[5], t_high);
    delay(2);
  } 

  for(int n=0;n<=5;n++) {
    analogWrite(led[n], 0);
  }
  
  delay(500);
}
