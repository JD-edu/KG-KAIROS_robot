const unsigned int led[6] = { 3, 5, 6, 9, 10, 11 };
const int buttonPin = 2;

void setup() {
  for(int x=0;x<=5;x++) {
    pinMode(led[x], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonInput = digitalRead(buttonPin);
  if(buttonInput==HIGH) {
    for(int x=0;x<=5;x++) {    
      for(int x=0;x<=5;x++) {  
        digitalWrite(led[x], LOW);
      }

      digitalWrite(led[x], HIGH);

      buttonInput = digitalRead(buttonPin);
      if(buttonInput==LOW) break;

      delay(50);
    }
  }
}
