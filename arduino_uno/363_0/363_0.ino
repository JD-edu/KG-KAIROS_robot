const int trig_pin = 3;
const int echo_pin = 4;

void setup() {  
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH);
  long distance = (duration/2) / 29.1;

  Serial.println(distance);
  delay(1000);

}
