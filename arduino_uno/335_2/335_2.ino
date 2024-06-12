const int led[6] = { 3, 5, 6, 9, 10, 11 };
const int analogPin = A0;

void setup() {
  for(int x=0;x<=5;x++) {
  pinMode(led[x], OUTPUT);
  }
}

void loop() {
  int sensorInput = analogRead(analogPin);

  for(int n=0;n<=5;n++) {
    
    if(sensorInput > 1024/7*(1+n))
      digitalWrite(led[n], HIGH);
    else digitalWrite(led[n], LOW);
    
  }
}
