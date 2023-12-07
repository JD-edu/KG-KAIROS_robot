#include<Servo.h>

Servo base;

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
    if (startPos < (thePos-5)){
       newPos = newPos + 1;               
       theServo.write(newPos);
       delay(speed);
       return 0;                          // Tell primary program that servo has not reached its position     
    }

    // Else if the current position is greater than the desired move the servo down
    else if (newPos > (thePos + 5)){
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
  Serial.begin(115200);
  base.attach(2);
  base.write(90);

}

void loop() {
  // These values are the status of whether or not the joint has reached its position yet
  // variables declared inside of some part of the program, like these, are called "local Variables"
  int status1 = 0;  //base status
  int status2 = 0;  //shoulder status
  int status3 = 0;  //elbow status
  int status4 = 0;  //gripper status

  int done = 0 ;    // this value tells when all the joints have reached thier positions

  if(Serial.available() > 0){
    char c = Serial.read();
    if(c == 'a'){
      while(done == 0){     // Loop until all joints have reached thier positions                      && ready == 1
        //move the servo to the desired position
        //This block of code uses "Functions" to make is more condensed.
        status1 = servoParallelControl(30, base, 20);         
        //status2 = servoParallelControl(desiredAngle.shoulder,  shoulderServo, desiredDelay);
        //status3 = servoParallelControl(desiredAngle.elbow, elbowServo, desiredDelay);      
        //status4 = servoParallelControl(desiredGrip, gripperServo, desiredDelay);  

        // Check whether all the joints have reached their positions
        if (status1 == 1 ){
          done = 1; //When done =1 then the loop will stop
          Serial.println("OK");
        }   
      }// end of while
    }else if(c == 'b'){
      while(done == 0){     // Loop until all joints have reached thier positions                      && ready == 1
        //move the servo to the desired position
        //This block of code uses "Functions" to make is more condensed.
        status1 = servoParallelControl(60, base, 20);         
        //status2 = servoParallelControl(desiredAngle.shoulder,  shoulderServo, desiredDelay);
        //status3 = servoParallelControl(desiredAngle.elbow, elbowServo, desiredDelay);      
        //status4 = servoParallelControl(desiredGrip, gripperServo, desiredDelay);  

        // Check whether all the joints have reached their positions
        if (status1 == 1 ){
          done = 1; //When done =1 then the loop will stop
          Serial.println("OK");
        }   
      }// end of while
    }
  }
}
