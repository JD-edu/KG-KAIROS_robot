int RED = 9;
int GREEN = 10;
int BLUE = 11;
int Trig=4;
int Echo=3;

void setup(){
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}
void loop(){
  digitalWrite(Trig,LOW);
  digitalWrite(Echo,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
 
  long distance = pulseIn(Echo, HIGH)/58.2;
  Serial.print("distance : ");
  Serial.print(distance);
  Serial.println("[cm]");

  if(distance <= 5){
    analogWrite(RED,255);
    analogWrite(GREEN,0);
    analogWrite(BLUE,0);
  }
  else if((distance <=10)){
    analogWrite(RED,255);
    analogWrite(GREEN,255);
    analogWrite(BLUE,0);
  }
  else{
    analogWrite(RED,0);
    analogWrite(GREEN,0);
    analogWrite(BLUE,255);
  }
}
