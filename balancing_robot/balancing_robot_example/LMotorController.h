/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/

#ifndef LMotorController_h
#define LMotorController_h


#include "Arduino.h"


class LMotorController
{
protected:
    int _ena, _in1, _in2, _enb, _in3, _in4;
    int _currentSpeed;
    double _motorAConst, _motorBConst;
public:
    LMotorController(int ena, int in1, int in2, int enb, int in3, int in4, double motorAConst, double motorBConst);
    void move(int leftSpeed, int rightSpeed, int minAbsSpeed);
    void move(int speed);
    void move(int speed, int minAbsSpeed);
    void turnLeft(int speed, bool kick);
    void turnRight(int speed, bool kick);
    void stopMoving();
};


#endif