const int trig_pin = 11;
const int echo_pin = 12;

void setup() {  
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(trig_pin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);

  unsigned long t_begin = millis();
  long duration = pulseIn(echo_pin, HIGH);
  unsigned long t_end = millis();
  Serial.print(t_end - t_begin);
  Serial.println(" ms");
}
