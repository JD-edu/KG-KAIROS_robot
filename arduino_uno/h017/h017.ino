int PIRsensor = 2; 

void setup(){
  Serial.begin(115200);
  pinMode(PIRsensor,INPUT);
  digitalWrite(PIRsensor,LOW);
}

void loop(){
  if(digitalRead(PIRsensor)==HIGH){
    Serial.println("Somebodyishere.");
  }
  else{
    Serial.println("Nobody.");
  }
  delay(1000);
}  
