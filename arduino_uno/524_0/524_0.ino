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
  digitalWrite(led[x], LOW);
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

void display_numbers(unsigned int num) {
  unsigned int num_1000 = num/1000;
  unsigned int num_100 = (num%1000)/100;
  unsigned int num_10 = (num%100)/10;
  unsigned int num_1 = num%10;
  
  display_number(num_1000, 1);
  delay(1);
  display_number(num_100, 2);
  delay(1);
  display_number(num_10, 3);
  delay(1);
  display_number(num_1, 4);
  delay(1);
}

void setup() {  
  display_init();
}

//void loop() {
//  static unsigned int num = 0;
//  num ++;
//  display_numbers(num);   
//}


void loop() {
  static unsigned int num = 0;
  num ++;

  unsigned int cnt = 0;
  while(1) {
  display_numbers(num);   
  cnt++;
  if(cnt == 25) break;
  }
}
