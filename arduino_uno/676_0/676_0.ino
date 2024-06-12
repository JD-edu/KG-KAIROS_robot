#include "NDelayFunc.h"
#include "DotMatrix.h"

unsigned int game_display[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 1, 0, 0, 0, 0},
  {-1, 0, 0, 1, 1, 1, 0, 0, 0},
};

const unsigned int game_lose[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 1, 1, 0, 0, 1, 1, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 1, 1, 1, 1, 0, 0},
  {-1, 0, 1, 0, 0, 0, 0, 1, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
};

const unsigned int game_win[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 1, 0, 0, 1, 0, 0},
  {-1, 0, 0, 1, 0, 0, 1, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 1, 0, 0, 0, 0, 1, 0},
  {-1, 0, 0, 1, 1, 1, 1, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
};

enum {PLAY=0, LOSE, WIN};
int game_state = PLAY;

int ball_x = 4;
int ball_x_dir = 1;
int ball_y = 7;
int ball_y_dir = 1;

int how_many_bricks = 24;

void ball_move() {

  if(game_state!=PLAY) return;
  
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
  if(game_display[ball_y][ball_x]==1) {
    ball_y-=2*ball_y_dir;
    ball_y_dir=-ball_y_dir;
  } else {
    game_state = LOSE;
    return;
  }
  }
  if(ball_y<=1) {
  ball_y=1;
  ball_y_dir=-ball_y_dir;
  }
  if(game_display[ball_y+ball_y_dir][ball_x]==1) {
  if(ball_y != 7) {
    game_display[ball_y+ball_y_dir][ball_x]=0;
    how_many_bricks--;
    if(how_many_bricks == 0) game_state = WIN;
  }
  ball_y_dir=-ball_y_dir;
  } else if(game_display[ball_y+ball_y_dir][ball_x+ball_x_dir]==1) {
  if(ball_y != 7) {
    game_display[ball_y+ball_y_dir][ball_x+ball_x_dir]=0;
    how_many_bricks--;
    if(how_many_bricks == 0) game_state = WIN;
  }
  ball_y_dir=-ball_y_dir;
  ball_x_dir=-ball_x_dir;
  }
  game_display[ball_y][ball_x] = 1;
}
NDelayFunc nDelayGame(500, ball_move);

void draw() {
  if(game_state==PLAY) DotMatrix.draw(game_display);
  else if(game_state==LOSE) DotMatrix.draw(game_lose);
  else if(game_state==WIN) DotMatrix.draw(game_win);
}
NDelayFunc nDelayDraw(1, draw);

int bar_x = 4;
const int bar_y = 8;

void bar_move() {  

  if(game_state!=PLAY) return;
  
  int analogValue = analogRead(A5);
  //Serial.println(analogValue);
  
  static int prevAnalogValue = 0;
  
  int new_bar_x = bar_x;
  
  if(analogValue > prevAnalogValue+1024/8) {
  prevAnalogValue = analogValue;
  new_bar_x++;
  if(new_bar_x>=7) new_bar_x = 7;
  Serial.println(new_bar_x);
  } else if(analogValue < prevAnalogValue-1024/8) {
  prevAnalogValue = analogValue;
  new_bar_x--;
  if(new_bar_x<=2) new_bar_x = 2;
  Serial.println(new_bar_x);
  } 

//  bar_x = new_bar_x;
  if(new_bar_x != bar_x) {
  game_display[bar_y][bar_x] = 0;
  game_display[bar_y][bar_x-1] = 0;
  game_display[bar_y][bar_x+1] = 0;
  
  bar_x = new_bar_x;
  
  game_display[bar_y][bar_x] = 1;
  game_display[bar_y][bar_x-1] = 1;
  game_display[bar_y][bar_x+1] = 1;
  }
} 
void setup() {
  DotMatrix.init();
  Serial.begin(115200);
}

void loop() {
  bar_move();
  nDelayGame.run();
  nDelayDraw.run();
}
