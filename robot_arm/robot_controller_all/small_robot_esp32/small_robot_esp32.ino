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

#include <ESP32Servo.h>

Servo base;
Servo shoulder;
Servo upperarm;
Servo forearm;

int baseAngle = 90;
int shoulderAngle = 90;
int upperarmAngle = 90;
int forearmAngle = 90;

int base_c = 90;
int shoulder_c = 90;
int upper_c = 90;
int fore_c = 90;

String baseAngle_str;
String shoulder_str;
String upperarm_str;
String forearm_str;
String inString;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int servoParallelControl (int thePos, int curr, Servo theServo, int speed){
    // This function moves a servo a certain number of steps toward a desired position and 
    // returns whether or not it is near or hase recahed that position
    // thePos - the desired position
    // thServo - the address pin of the servo that we want to move
    // theSpeed - the delay between steps of the servo
    
    int startPos = curr; //theServo.read();       //read the current position of the servo we are working with.
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


void setup() {
  // put your setup code here, to run once:
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  Serial.begin(115200);
  base.setPeriodHertz(50);  
  base.attach(5, 500, 2400);
 
  shoulder.setPeriodHertz(50);  
  shoulder.attach(21, 500, 2400);
  
  upperarm.setPeriodHertz(50);  
  upperarm.attach(18, 500, 2400);
  
  forearm.setPeriodHertz(50);  
  forearm.attach(19, 500, 2400);
  
  delay(2000);
  base.write(baseAngle);
  shoulder.write(shoulderAngle);
  upperarm.write(upperarmAngle);
  forearm.write(forearmAngle);
}

void loop() {
  delay(100);
  //Serial.println(baseAngle);
  
    if(Serial.available()){
      inString = Serial.readStringUntil('\n');
      char cmd = inString[0];
      if(cmd == '1'){
        Serial.println(cmd);
       
        Serial.print('a');
        Serial.print(base_c);
        Serial.print('b');
        Serial.print(shoulder_c);
        Serial.print('c');
        Serial.print(upper_c);
        Serial.print('d');
        Serial.print(fore_c);
        Serial.println('e');
      }else if(cmd == '2'){
        // angle 0
        Serial.println(cmd);
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
        Serial.print(" ");
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
          Serial.print("siva");
          status1 = servoParallelControl(baseAngle, base_c,  base, 30);         
          status2 = servoParallelControl(shoulderAngle, shoulder_c, shoulder, 30);
          status3 = servoParallelControl(upperarmAngle, upper_c, upperarm, 30);      
          status4 = servoParallelControl(forearmAngle, fore_c, forearm, 30);  

          // Check whether all the joints have reached their positions
          if (status1 == 1 && status2 == 1 && status3 == 1 && status4 == 1){
          //if (status3 == 1){
            done = 1; //When done =1 then the loop will stop
          }   
        }// end of while
        base_c = baseAngle;
        shoulder_c = shoulderAngle;
        upper_c = upperarmAngle;
        fore_c = forearmAngle;
      
        delay(100);
      }else if(cmd == '3'){
        int done = 0;
        int status1 = 0;  //base status
        int status2 = 0;  //shoulder status
        int status3 = 0;  //elbow status
        int status4 = 0;  //gripper status
        while(done == 0){     // Loop until all joints have reached thier positions                      && ready == 1
            //move the servo to the desired position
            //This block of code uses "Functions" to make is more condensed.
            status1 = servoParallelControl(90, base_c, base, 20);         
            status2 = servoParallelControl(90, shoulder_c, shoulder, 20);
            status3 = servoParallelControl(90, upper_c, upperarm, 20);      
            status4 = servoParallelControl(90, fore_c, forearm, 20);  

            // Check whether all the joints have reached their positions
            if (status1 == 1 && status2 == 1 && status3 == 1 && status4 == 1){
            //if (status3 == 1){
              done = 1; //When done =1 then the loop will stop
            }   
          }// end of while
      }
    }
  
}
