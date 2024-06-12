#include "NDelayFunc.h"
#include "DotMatrix.h"

const unsigned int heart[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 1, 1, 0, 0, 1, 1, 0},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1, 0, 1, 1, 1, 1, 1, 1, 0},
  {-1, 0, 0, 1, 1, 1, 1, 0, 0},
  {-1, 0, 0, 0, 1, 1, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
};

const unsigned int heart_small[1+8][1+8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 1, 0, 0, 1, 0, 0},
  {-1, 0, 1, 1, 1, 1, 1, 1, 0},
  {-1, 0, 0, 1, 1, 1, 1, 0, 0},
  {-1, 0, 0, 0, 1, 1, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1, 0, 0, 0, 0, 0, 0, 0, 0},
};

int heart_state = 0;
void choose() {
  heart_state++;
  if(heart_state>1) heart_state = 0;  
}
NDelayFunc nDelayChoose(500, choose);

void draw() {
  if(heart_state == 0) DotMatrix.draw(heart);
  else if(heart_state == 1) DotMatrix.draw(heart_small);
}
NDelayFunc nDelayDraw(1, draw);

void setup() {
  DotMatrix.init();
}

void loop() {
  nDelayChoose.run();
  nDelayDraw.run();
}
