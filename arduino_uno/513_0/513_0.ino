const unsigned int led_a = 2;
const unsigned int led_b = 3;
const unsigned int led_c = 4;
const unsigned int led_d = 5;
const unsigned int led_e = 6;
const unsigned int led_f = 7;
const unsigned int led_g = 8;

void setup() {
  // led 초기화
  pinMode(led_a, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_c, OUTPUT);
  pinMode(led_d, OUTPUT);
  pinMode(led_e, OUTPUT);
  pinMode(led_f, OUTPUT);
  pinMode(led_g, OUTPUT);

  // led 켜기
  digitalWrite(led_a, HIGH); 
  digitalWrite(led_b, HIGH);
  digitalWrite(led_c, HIGH);
  digitalWrite(led_d, HIGH);
  digitalWrite(led_e, HIGH);
  digitalWrite(led_f, HIGH);
  digitalWrite(led_g, HIGH);  
}

void loop() {
  
}
