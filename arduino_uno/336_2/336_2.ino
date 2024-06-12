const int led[6] = { 3, 5, 6, 9, 10, 11 };
const int analogPin = A0;

void setup() {
  
}

void loop() {
  int sensorInput = analogRead(analogPin);

  for(int n=0;n<=5;n++) {
    
    if(sensorInput/171>=1+n) // 171*(1+n) 이상이면
      analogWrite(led[n], 255);
    else if(sensorInput/171>=0+n) // 171*(0+n) 이상이면
      analogWrite(led[n], int(sensorInput%171/171.0*255));
    
  }
}
