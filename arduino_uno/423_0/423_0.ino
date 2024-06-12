const int ACTIVE_BUZZER = 10;
const int buttonPin = 2;

int buzzer_state = LOW;
bool buzzer_state_changed = false;

void buttonPressed() {
  buzzer_state = (buzzer_state == LOW)?HIGH:LOW;
  buzzer_state_changed = true;
}

void setup() {
  pinMode(ACTIVE_BUZZER, OUTPUT);  
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, RISING);
}

void loop() {
  if(buzzer_state_changed) {
  buzzer_state_changed = false;
  digitalWrite(ACTIVE_BUZZER, buzzer_state);
  }   
}
