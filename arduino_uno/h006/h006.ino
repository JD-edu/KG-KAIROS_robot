const int led[6] = { 3, 5, 6, 9, 10, 11 };
const int analogPin = A0;

void setup() {

}

void loop() {
  int sensorInput = analogRead(analogPin);
  int level = map(sensorInput, 0, 1023, 0, 6);
  for(int n=0; n<6; n++){
    if(n<level){
      analogWrite(led[n],255);
    }
    else{
      analogWrite(led[n],0);
    }
  }
}
