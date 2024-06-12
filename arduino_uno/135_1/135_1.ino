int f(int x) {
  return x+1;
}

void setup() {
  Serial.begin(115200);
  
  int x = 2;
  int y = f(x);

  Serial.println(y);
}

void loop() {

}
