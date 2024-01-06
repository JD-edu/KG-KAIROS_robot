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

#include<Servo.h>
#include <U8x8lib.h>

Servo base;
Servo shoulder;
Servo upperarm;
Servo forearm;



int baseAngle = 90;
int shoulderAngle = 90;
int upperarmAngle = 90;
int forearmAngle = 90;

String baseAngle_str;
String shoulder_str;
String upperarm_str;
String forearm_str;
String inString;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

int servoParallelControl (int thePos, Servo theServo, int speed){
    // This function moves a servo a certain number of steps toward a desired position and 
    // returns whether or not it is near or hase recahed that position
    // thePos - the desired position
    // thServo - the address pin of the servo that we want to move
    // theSpeed - the delay between steps of the servo
    
    int startPos = theServo.read();       //read the current position of the servo we are working with.
    int newPos = startPos;                // newPos holds the position of the servo as it moves
    
    //define where the pos is with respect to the command
    // if the current position is less that the desired move the position up
    if (startPos < (thePos)){
       newPos = newPos + 1;               
       theServo.write(newPos);
       delay(speed);
       return 0;                          // Tell primary program that servo has not reached its position     
    }

    // Else if the current position is greater than the desired move the servo down
    else if (newPos > (thePos)){
      newPos = newPos - 1;
      theServo.write(newPos);
      delay(speed);
      return 0;  
    }  

    // If the servo is +-5 within the desired range then tell the main program that the servo has reached the desired position.
    else {
        return 1;
    }  
}

void clear_oled(){
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"                   ");
  u8x8.drawString(0,1,"                   ");
  u8x8.drawString(0,2,"                   ");
  u8x8.drawString(0,3,"                   ");
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  base.attach(2);
  base.write(baseAngle);
  shoulder.attach(3);
  shoulder.write(shoulderAngle);
  upperarm.attach(4);
  upperarm.write(upperarmAngle);
  forearm.attach(5);
  forearm.write(forearmAngle);
  u8x8.begin();
  u8x8.setPowerSave(0);

}

void loop() {
  if (Serial.available() > 0){  
    if(Serial.available()){
      inString = Serial.readStringUntil('\n');
      char cmd = inString[0];
      if(cmd == '1'){
        clear_oled();
        u8x8.drawString(0,0,"read angles");
        Serial.print('a');
        Serial.print(baseAngle);
        Serial.print('b');
        Serial.print(shoulderAngle);
        Serial.print('c');
        Serial.print(upperarmAngle);
        Serial.print('d');
        Serial.print(forearmAngle);
        Serial.println('e');
      }else if(cmd == '2'){
        // angle 0
        int first = inString.indexOf('a');
        int second = inString.indexOf('b');
        baseAngle_str = inString.substring(first+1, second);
        baseAngle = baseAngle_str.toInt();    
        Serial.print(baseAngle);
        Serial.print(" ");
        // angle 1
        first = inString.indexOf('b');
        second = inString.indexOf('c');
        shoulder_str = inString.substring(first+1, second);
        shoulderAngle = shoulder_str.toInt();
        Serial.print(shoulderAngle);
        Serial.print(" ");
        // angle 2
        first = inString.indexOf('c');
        second = inString.indexOf('d');
        upperarm_str = inString.substring(first+1, second);
        upperarmAngle = upperarm_str.toInt();
        Serial.print(upperarmAngle);
        // angle 3
        first = inString.indexOf('d');
        second = inString.indexOf('e');
        forearm_str = inString.substring(first+1, second);
        forearmAngle = forearm_str.toInt();
        Serial.print(forearmAngle);
        Serial.println(" ");
        // These values are the status of whether or not the joint has reached its position yet
        // variables declared inside of some part of the program, like these, are called "local Variables"
        int status1 = 0;  //base status
        int status2 = 0;  //shoulder status
        int status3 = 0;  //elbow status
        int status4 = 0;  //gripper status

        int done = 0 ;    // this value tells when all the joints have reached thier positions

        while(done == 0){     // Loop until all joints have reached thier positions                      && ready == 1
          //move the servo to the desired position
          //This block of code uses "Functions" to make is more condensed.
          status1 = servoParallelControl(baseAngle, base, 20);         
          status2 = servoParallelControl(shoulderAngle, shoulder, 20);
          status3 = servoParallelControl(upperarmAngle, upperarm, 20);      
          status4 = servoParallelControl(forearmAngle, forearm, 20);  

          // Check whether all the joints have reached their positions
          if (status1 == 1 && status2 == 1 && status3 == 1 && status4 == 1){
          //if (status3 == 1){
            done = 1; //When done =1 then the loop will stop
          }   
        }// end of while
        clear_oled();
        u8x8.setFont(u8x8_font_chroma48medium8_r);
        u8x8.drawString(0,0,inString.c_str());
        u8x8.drawString(0,1,baseAngle_str.c_str());
        u8x8.drawString(0,2,shoulder_str.c_str());
        u8x8.drawString(0,3,upperarm_str.c_str());
        delay(100);
      }
    }

   
    
  }
}
