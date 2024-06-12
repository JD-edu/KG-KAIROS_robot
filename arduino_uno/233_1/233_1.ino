const unsigned int led_0 = 2;
const unsigned int led_1 = 3;
const unsigned int led_2 = 4;
const unsigned int led_3 = 5;
const unsigned int led_4 = 6;
const unsigned int led_5 = 7;
const unsigned int led_6 = 8;
const unsigned int led_7 = 9;

void setup() {
  // led 초기화
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);
  pinMode(led_7, OUTPUT);

  // led 켜기
  digitalWrite(led_0, HIGH);
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
  digitalWrite(led_4, HIGH);
  digitalWrite(led_5, HIGH);
  digitalWrite(led_6, HIGH);  
  digitalWrite(led_7, HIGH);  
}

void loop() {
  
}
