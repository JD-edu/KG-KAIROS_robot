void setup() {
  Serial.begin(115200);
}

void loop() {
  for(int i=0; i<5; i++){
    for(int j=0; i<5; j++){
      Serial.print("*");      
    }
    Serial.println();
  }
}
