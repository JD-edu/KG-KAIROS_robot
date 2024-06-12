const int BUZZER = 10;

const int melody[8] = {
  262, 294, 330, 349, 393, 440, 494, 523,  
};

void setup() {
  for(int note=0;note<=7;note++) {
    tone(BUZZER, melody[note],250);     
    delay(500);
  }
  
  noTone(BUZZER);
}

void loop() {
  
}
