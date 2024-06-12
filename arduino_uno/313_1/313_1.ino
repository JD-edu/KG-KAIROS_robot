const int LED = 10;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    char userInput = Serial.read();
    
    switch(userInput) {
      case '0': analogWrite(LED, 0); break;
      case '1': analogWrite(LED, 25*1); break;
      case '2': analogWrite(LED, 25*2); break;
      case '3': analogWrite(LED, 25*3); break;
      case '4': analogWrite(LED, 25*4); break;
      case '5': analogWrite(LED, 25*5); break;
      case '6': analogWrite(LED, 25*6); break;
      case '7': analogWrite(LED, 25*7); break;
      case '8': analogWrite(LED, 25*8); break;
      case '9': analogWrite(LED, 25*9); break;
      default: break;
    }
  }  
}
