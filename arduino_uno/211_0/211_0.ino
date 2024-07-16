void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  int uga = Serial.available();
  if( uga > 0){
    char c = Serial.read();
    if (c == 'a'){
      digitalWrite(13, HIGH);
    }else if(c == 'b'){
      digitalWrite(13, LOW);
    }
  }
}
