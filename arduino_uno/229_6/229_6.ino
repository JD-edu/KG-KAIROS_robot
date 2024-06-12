void setup() {
  Serial.begin(115200);

  int t_high=0;
  while(true) {
    Serial.println(t_high);

    t_high++;
    if(t_high>10) break;
  }
}

void loop() {
  
}
