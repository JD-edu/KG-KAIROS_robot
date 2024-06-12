const int ledPin =  13;
const int buttonPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);  
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonInput = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonInput);  
}
