void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    char userInput = Serial.read();
    Serial.print(userInput);
  }  
}
