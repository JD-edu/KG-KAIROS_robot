const int buttonPin = 2;    
const int ledPin = 3;      

int ledState = HIGH;        
int buttonState= HIGH;            
int lastButtonState = LOW;  

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;   

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
