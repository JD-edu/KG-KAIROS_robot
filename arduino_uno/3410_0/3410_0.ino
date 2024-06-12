const int ACTIVE_BUZZER = 10;
const int buttonPin = 2;

void setup() {
  pinMode(ACTIVE_BUZZER, OUTPUT);  
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonInput = digitalRead(buttonPin);
  digitalWrite(ACTIVE_BUZZER, buttonInput);  
}
