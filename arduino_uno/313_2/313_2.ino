void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    int userInput = Serial.read();
    
    switch(userInput) {
      case '1': 
        Serial.println(1);
        break;
      case '2':
        Serial.println(2);
      case '3': 
        Serial.println(3);
        break;
      default: 
        Serial.println(userInput);
        break;
    }
  }
}
