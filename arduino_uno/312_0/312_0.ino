const int LED = 13;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    char userInput = Serial.read();
    
    switch(userInput) {
      case 'n':
        digitalWrite(LED, HIGH);
        break;
      
      case 'f':
        digitalWrite(LED, LOW);
        break;
      
      default:
        break;
    }
  }  
}
