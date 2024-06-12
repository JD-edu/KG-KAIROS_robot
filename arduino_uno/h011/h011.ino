void setup() {
  Serial.begin(115200);
}

void loop() {
  char i,j;

  for(i='F'; i>='A'; i--){
    for(j='F'; j>=i; j--){
      Serial.print(j);
    }  
    Serial.print('\n');
  }
  for(;;);
}
