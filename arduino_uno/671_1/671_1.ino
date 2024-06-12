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

int ball_x = 4;
int ball_x_dir = 1;
int ball_y = 7;
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
  if(game_display[ball_y][ball_x]==1)
    ball_y-=2*ball_y_dir;
  ball_y_dir=-ball_y_dir;
  }
  if(ball_y<=1) {
  ball_y=1;
  ball_y_dir=-ball_y_dir;
  }
  if(game_display[ball_y+ball_y_dir][ball_x]==1) {
  if(ball_y != 7)
    game_display[ball_y+ball_y_dir][ball_x]=0;
  ball_y_dir=-ball_y_dir;
  } else if(game_display[ball_y+ball_y_dir][ball_x+ball_x_dir]==1) {
  if(ball_y != 7)
    game_display[ball_y+ball_y_dir][ball_x+ball_x_dir]=0;
  ball_y_dir=-ball_y_dir;
  ball_x_dir=-ball_x_dir;
  }
  game_display[ball_y][ball_x] = 1;
}
NDelayFunc nDelayGame(500, ball_move);

void draw() {
  DotMatrix.draw(game_display);
}
NDelayFunc nDelayDraw(1, draw);

void setup() {
  DotMatrix.init();
}

void loop() {
  nDelayGame.run();
  nDelayDraw.run();
}
