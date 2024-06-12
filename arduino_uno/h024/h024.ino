int A_IA = 10;   
int A_IB = 9;
int ENCODER = 11;
volatile int count = 0;
unsigned long oldTime = 0;
unsigned long newTime = 0;

void ISRencoder(){
  count++;
}

void setup() {
  Serial.begin(115200);
  pinMode(A_IA,OUTPUT);
  pinMode(A_IB,OUTPUT);
  pinMode(ENCODER,INPUT_PULLUP);
  attachInterrupt(INT1,ISRencoder,FALLING);
}

void loop() {
  if (Serial.available()>0){
    char c = Serial.read();
    if(c=='f'){
      analogWrite(A_IA,128);
      analogWrite(A_IB,0);
    }
    else if(c=='s'){
      analogWrite(A_IA,0);
      analogWrite(A_IB,0);
    }
  }  
  newTime = millis();
  if(newTime-oldTime > 1000){
    oldTime = newTime;
    noInterrupts();
    Serial.print("cnt : ");
    Serial.println(count);
    count = 0;
    interrupts();
  }
 }
