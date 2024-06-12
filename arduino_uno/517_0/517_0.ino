const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };

void display_init() {  
  for(int x=0;x<7;x++) {
  pinMode(led[x], OUTPUT);
  }   
}

void display_clear() {
  for(int x=0;x<7;x++) {
  digitalWrite(led[x], LOW);
  }
}

void setup() {  
  display_init();  
}

void loop() {
  for(int x=0;x<7;x++) {
  
  display_clear();
  
  digitalWrite(led[x], HIGH);
  
  delay(1);//1/7=0.143Hz
  }
}
