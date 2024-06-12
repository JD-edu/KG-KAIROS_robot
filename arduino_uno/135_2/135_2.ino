float g(float x) {
  return x+1;
}

void setup() {
  Serial.begin(115200);
  
  float x = 2.1;
  float y = g(x);

  Serial.println(y);
}

void loop() {

}
