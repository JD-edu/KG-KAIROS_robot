enum { R5=1,R7,C2,C3,R8,C5,R6,R3,R1,C4,C6,R4,C1,R2,C7,C8 };
const unsigned int pins[1+16] = {
  -1, 10,11,12,13,14,15,16,17, 2,3,4,5,6,7,8,9
};

const unsigned int R[1+8] = { -1, R1, R2, R3, R4, R5, R6, R7, R8 };
const unsigned int C[1+8] = { -1, C1, C2, C3, C4, C5, C6, C7, C8 };

unsigned int game_display[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 1, 0, 0, 0, 0},
};

int ball_x = 4;
int ball_x_dir = 1;
int ball_y = 8;
int ball_y_dir = 1;

void ball_move() {
  game_display[ball_y][ball_x] = 0;    
  ball_x += ball_x_dir;
  if(ball_x>=8) {
  ball_x=8;
  ball_x_dir=-ball_x_dir;
  }
  if(ball_x<=1) {
  ball_x=1;
  ball_x_dir=-ball_x_dir;
  }
  ball_y += ball_y_dir;
  if(ball_y>=8) {
  ball_y=8;
  ball_y_dir=-ball_y_dir;
  }
  if(ball_y<=1) {
  ball_y=1;
  ball_y_dir=-ball_y_dir;
  }
  game_display[ball_y][ball_x] = 1;
}

void dot_matrix_init() {
  // 도트 매트릭스 핀 초기화
  for(int n=1;n<=8;n++) {
  pinMode(pins[R[n]], OUTPUT);
  pinMode(pins[C[n]], OUTPUT);
  } 
  
  // 도트 매트릭스 끄기 
  for(int n=1;n<=8;n++) {
  digitalWrite(pins[R[n]], HIGH);
  digitalWrite(pins[C[n]], HIGH);
  }
}

void dot_matrix_draw(const unsigned int image[1+8][1+8]) {
   // 도트 매트릭스 그리기
  for(int n=1;n<=8;n++) {
  // 열을 꺼준다.
  if(n>1) digitalWrite(pins[R[n-1]], HIGH);
  if(n==1) digitalWrite(pins[R[8]], HIGH);

  // 행을 켤 준비를 한다.
  for(int m=1;m<=8;m++) {
    if(image[n][m] == 1)
    digitalWrite(pins[C[m]], HIGH);
    else digitalWrite(pins[C[m]], LOW);
  }
  
  // 열을 켜준다.
  for(int m=1;m<=8;m++) {
    if(image[n][m] == 1) {
    digitalWrite(pins[R[n]], LOW);
    break;
    }
  }
    
  delay(1);
  } 
}

void setup() {
  dot_matrix_init();
}

//void loop() {
//  ball_move();
//  
//  dot_matrix_draw(game_display);
//}

void loop() {
  ball_move();

  int cnt = 0;
  while(1) {
  dot_matrix_draw(game_display);
  cnt++;
  if(cnt==63) break;
  }
}
