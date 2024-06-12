const int Xin= A0; // 조이스틱 X 좌표 입력 핀
const int Yin = A1; // 조이스틱 Y 좌표 입력 핀
const int KEYin = 3; // 조이스틱 푸시버튼 입력 핀

void setup () {
  pinMode (KEYin, INPUT);
  Serial.begin (115200); 
}

void loop () {
  int xVal = analogRead (Xin);
  int yVal = analogRead (Yin);
  int buttonVal = digitalRead (KEYin);
  
  Serial.print("X = ");
  Serial.println (xVal, DEC);
  
  Serial.print ("Y = ");
  Serial.println (yVal, DEC);
  
  Serial.print("Button is ");
  if (buttonVal == HIGH) {
  Serial.println ("not pressed");
  } else {
  Serial.println ("PRESSED");
  }
}
