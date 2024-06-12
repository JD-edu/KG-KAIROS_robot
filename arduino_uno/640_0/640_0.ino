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

void draw() {
  DotMatrix.draw(heart);
}
NDelayFunc nDelayDraw(1, draw);

void setup() {
  DotMatrix.init();
}

void loop() {
  nDelayDraw.run();
}
