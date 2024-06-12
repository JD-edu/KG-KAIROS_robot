const unsigned int led[7] = { 2, 3, 4, 5, 6, 7, 8 };

const unsigned int num[2][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },/*0*/
  { 0, 1, 1, 0, 0, 0, 0 }/*1*/
};

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

void display_number(int n) {
  if(0<=n&&n<=1) {
  for(int x=0;x<7;x++) {
    digitalWrite(led[x], num[n][x]==1?HIGH:LOW);
  }
  }
}

void setup() {  
  display_init();
}

void loop() {
  for(int n=0;n<=1;n++) {
  display_clear();
  display_number(n);
  delay(500);
  }
}
