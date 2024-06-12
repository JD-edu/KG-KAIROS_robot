const int analogPin = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int analogValue = analogRead(analogPin);
  Serial.println(analogValue);
}
