const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };
const unsigned int com[1+4] = { -1, 9, 10, 11, 12 };

const unsigned int num[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0, },/*0*/
  { 0, 1, 1, 0, 0, 0, 0, },/*1*/
  { 1, 1, 0, 1, 1, 0, 1, },/*2*/
  { 1, 1, 1, 1, 0, 0, 1, },/*3*/
  { 0, 1, 1, 0, 0, 1, 1, },/*4*/
  { 1, 0, 1, 1, 0, 1, 1, },/*5*/
  { 1, 0, 1, 1, 1, 1, 1, },/*6*/
  { 1, 1, 1, 0, 0, 1, 0, },/*7*/
  { 1, 1, 1, 1, 1, 1, 1, },/*8*/
  { 1, 1, 1, 1, 0, 1, 1, },/*9*/
};

void display_init() {  
  for(int x=0;x<7;x++) {
  pinMode(led[x], OUTPUT);
  }
  for(int y=1;y<=4;y++) {
  pinMode(com[y], OUTPUT);
  }   
}

void display_clear() {
  for(int x=0;x<7;x++) {
  digitalWrite(led[x], );
  }
  for(int y=1;y<=4;y++) {
  digitalWrite(com[y], HIGH);
  }
}

void display_number(unsigned int n, unsigned int m) {
  
  display_clear();
  
  if(0<=n&&n<=9 && 1<=m&&m<=4) {
  for(int x=0;x<7;x++) {
    digitalWrite(led[x], num[n][x]==1?HIGH:LOW);
  }
  digitalWrite(com[m], LOW);
  }
}

void setup() {  
  display_init();
}

void loop() {
  display_number(1, 1);
  delay(1);
  display_number(2, 2);
  delay(1);
  display_number(3, 3);
  delay(1);
  display_number(4, 4);
  delay(1);  
}
