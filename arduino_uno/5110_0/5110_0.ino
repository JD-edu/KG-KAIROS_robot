const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };

const unsigned int num_0[7] = { 1, 1, 1, 1, 1, 1, 0 };/*0*/
const unsigned int num_1[7] = { 0, 1, 1, 0, 0, 0, 0 };/*1*/

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

void display_0() {
  for(int x=0;x<7;x++) {
  digitalWrite(led[x], num_0[x]==1?HIGH:LOW);
  }
}

void display_1() {
  for(int x=0;x<7;x++) {
  digitalWrite(led[x], num_1[x]==1?HIGH:LOW);
  }
}

void setup() {  
  display_init();
}

void loop() {
  display_clear();
  display_0();
  delay(500);
  
  display_clear();
  display_1();
  delay(500);
}
