#ifndef DotMatrix_h_
#define DotMatrix_h_

enum { R5=1,R7,C2,C3,R8,C5,R6,R3,R1,C4,C6,R4,C1,R2,C7,C8 };

class _DotMatrix {
  static const unsigned int pins[1+16];
  static const unsigned int R[1+8];
  static const unsigned int C[1+8];

public:
  static void init();
  static void draw(const unsigned int image[1+8][1+8]);
};

extern _DotMatrix DotMatrix;
#endif