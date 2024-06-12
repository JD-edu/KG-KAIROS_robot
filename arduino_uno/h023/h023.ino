const int buttonPin = 2;    
const int Speed = 10;
const int Wheel = 9;

int DCspeed = 0;
int buttonState = HIGH;  
int lastButtonState = HIGH;  

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 

void motor(int data){
  digitalWrite(Wheel,LOW);
  analogWrite(Speed,data);
}

void setup() {
  pinMode(Speed,OUTPUT);
  pinMode(Wheel,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  analogWrite(Speed,0);
  digitalWrite(Wheel,0);
  Serial.begin(115200);
}

void loop(){
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        DCspeed += 120;
        if(DCspeed >=300){
          DCspeed=0;
        }
        Serial.println(DCspeed);
      }
    }
  }
  lastButtonState = reading;
  motor(DCspeed);  
}
