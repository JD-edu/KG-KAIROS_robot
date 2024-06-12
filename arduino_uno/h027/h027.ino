void setup() {
  Serial.begin(115200);
}

void loop() {
  for(int i=0; i<5; i++){
    for(int j=5; i<0; j--){
      Serial.print(" ");      
    }
    for(int z=1; z<=9; z+=2){
      Serial.print("*");      
    }
    Serial.println();
  }
}
