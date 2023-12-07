/*        

*/
#include <nRF24L01.h>
#include <RF24.h>
#include <VarSpeedServo.h>

// Define 6 servo home position arduino angle 
#define SERVO_0_HOME  90
#define SERVO_1_HOME  120
#define SERVO_2_HOME  160
#define SERVO_3_HOME  0
#define SERVO_4_HOME  80
#define SERVO_5_HOME  160

#define BAS_SERVO   0
#define SHL_SERVO   1
#define ELB_SERVO   2
#define WRI_SERVO   3
#define WRO_SERVO   4
#define GRI_SERVO   5

#define MOVE_ROBOT  0x04
#define SAVE_ROBOT  0x02
#define RUN_ROBOT   0x01
#define RESET_ROBOT 0x03

// nRF24L01 define CE and CSN 
RF24 radio(7, 8); 
// nRF24L01 address. same tx device and rx device
const byte address = '1'; 
// RF rx buffer
char rf_rx_buffer[13] = "";

// Servo instance 
VarSpeedServo bas_servo;
VarSpeedServo shl_servo;
VarSpeedServo elb_servo;
VarSpeedServo wri_servo;
VarSpeedServo wro_servo;
VarSpeedServo gri_servo;

// servo current position
int servo0Pos = SERVO_0_HOME, servo1Pos = SERVO_1_HOME, servo2Pos = SERVO_2_HOME, servo3Pos = SERVO_3_HOME, servo4Pos = SERVO_4_HOME, servo5Pos = SERVO_5_HOME; 
// servo destination position 
int servo00SP, servo01SP, servo02SP, servo03SP, servo04SP, servo05SP; 
// servo speed delay
int speedDelay = 10;

// joystick value 
unsigned int joy_1_h = 500; // base servo 
unsigned int joy_1_v = 500; // shoulder servo 
unsigned int joy_2_h = 500; // elbow servo 
unsigned int joy_2_v = 500; // wrist turn servo 
unsigned int joy_3_h = 500; // wrist up/down servo 
unsigned int joy_3_v = 500; // gripper servo 

// flag for representing robot is running now
bool run_robot_flag = false;

/*
  Description: Function for set robot arm home position
*/
void reset_arm_position(){
  int i = 0;
  /*--------------------- servo 0 ---------------------*/ 
  bas_servo.write(SERVO_0_HOME, 100, true);
  /*--------------------- servo 1 ---------------------*/ 
  shl_servo.write(SERVO_1_HOME, 100, true);
  /*--------------------- servo 2 ---------------------*/ 
  elb_servo.write(SERVO_2_HOME, 100, true);
  /*--------------------- servo 3 ---------------------*/ 
  wri_servo.write(SERVO_3_HOME, 100, true);
  /*--------------------- servo 4 ---------------------*/ 
  wro_servo.write(SERVO_4_HOME, 100, true);
  /*--------------------- servo 5 ---------------------*/ 
  gri_servo.write(SERVO_5_HOME, 100, true);
}

/*
  Description: converting 2 byte into int
*/
unsigned int BitShiftCombine( unsigned char x_high, unsigned char x_low)
{
  unsigned int combined; 
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in                                                             //rightmost 8 bits
  return combined;
}



void move__robot(){
 
  /*--------------------- servo 0 ---------------------*/ 
  bas_servo.write(servo0Pos, 50, true);
  /*--------------------- servo 1 ---------------------*/ 
  shl_servo.write(servo1Pos, 50, true);
  /*--------------------- servo 2 ---------------------*/ 
  elb_servo.write(servo2Pos, 50, true);
  /*--------------------- servo 3 ---------------------*/ 
  wri_servo.write(servo3Pos, 50, true);
  /*--------------------- servo 4 ---------------------*/ 
  wro_servo.write(servo4Pos, 50, true);
  /*--------------------- servo 5 ---------------------*/ 
  gri_servo.write(SERVO_5_HOME, 50, true);
}

/*============================= robot control functions ===========================*/ 

/*
  Description: Function for programming robot using joystick through nRF24L01
*/
void move_robot(){

  int temp_servo0, temp_servo1, temp_servo2, temp_servo3, temp_servo4, temp_servo5;
  //Serial.println("program robot");
  joy_1_h = BitShiftCombine(rf_rx_buffer[2], rf_rx_buffer[1]);
  joy_1_v = BitShiftCombine(rf_rx_buffer[4], rf_rx_buffer[3]);

  joy_2_h = BitShiftCombine(rf_rx_buffer[6], rf_rx_buffer[5]);
  joy_2_v = BitShiftCombine(rf_rx_buffer[8], rf_rx_buffer[7]);

  joy_3_h = BitShiftCombine(rf_rx_buffer[10], rf_rx_buffer[9]);
  joy_3_v = BitShiftCombine(rf_rx_buffer[12], rf_rx_buffer[11]);

  /*--------------------- servo 0 ---------------------*/ 
  if(joy_1_h > 800){
    servo0Pos++;
    if(servo0Pos > 180){
      servo0Pos = 180;
    }
    bas_servo.write(servo0Pos, 0, true);
  }else if(joy_1_h < 200){
    servo0Pos--;
    if(servo0Pos < 0){
      servo0Pos = 0;
    }
    bas_servo.write(servo0Pos, 0, true);
  }
  delay(speedDelay);
  /*--------------------- servo 1 ---------------------*/ 
  if(joy_1_v > 800){
    servo1Pos++;
    if(servo1Pos > 180){
      servo1Pos = 180;
    }
    shl_servo.write(servo1Pos, 0, true);
  }else if(joy_1_v < 200){
    servo1Pos--;
    if(servo1Pos < 0){
      servo1Pos = 0;
    }
    shl_servo.write(servo1Pos, 0, true);
  }
  delay(speedDelay);
  /*--------------------- servo 2 ---------------------*/ 
  if(joy_2_v < 200){
    servo2Pos++;
    if(servo2Pos > 180){
      servo2Pos = 180;
    }
    elb_servo.write(servo2Pos, 0, true);
  }else if(joy_2_v > 800){
    servo2Pos--;
    if(servo2Pos < 0){
      servo2Pos = 0;
    }
    elb_servo.write(servo2Pos, 0, true);

  }
  delay(speedDelay);
  /*--------------------- servo 3 ---------------------*/ 
  if(joy_2_h > 800){
    servo3Pos++;
    if(servo3Pos > 180){
      servo3Pos = 180;
    }
    wri_servo.write(servo3Pos, 0, true);
  }else if(joy_2_h < 200){
    servo3Pos--;
    if(servo3Pos < 0){
      servo3Pos = 0;
    }
    wri_servo.write(servo3Pos, 0, true);
  }
  /*--------------------- servo 4 ---------------------*/ 
  if(joy_3_h > 800){
    servo4Pos++;
    if(servo4Pos > 180){
      servo4Pos = 180;
    }
    wro_servo.write(servo4Pos, 0, true);
  }else if(joy_3_h < 200){
    servo4Pos--;
    if(servo4Pos < 0){
      servo4Pos = 0;
    }
    wro_servo.write(servo4Pos, 0, true);
  }
  /*--------------------- servo 5 ---------------------*/ 
  if(joy_3_v > 800){
    servo5Pos++;
    if(servo5Pos > 180){
      servo5Pos = 180;
    }
    gri_servo.write(servo5Pos, 0, true);
  }else if(joy_3_v < 200){
    servo5Pos--;
    if(servo5Pos < 0){
      servo5Pos = 0;
    }
    gri_servo.write(servo5Pos, 0, true);
  }
  delay(speedDelay);

  temp_servo0 = servo0Pos;
  temp_servo1 = servo1Pos;
  temp_servo2 = servo2Pos;
  temp_servo3 = servo3Pos;
  temp_servo4 = servo4Pos;
  temp_servo5 = servo5Pos;

  temp_servo0 -= 90;
  temp_servo1 -= 90;
  temp_servo2 = (180-temp_servo2)-90;
  temp_servo3 -= 90;
  temp_servo4 -= 90;
  temp_servo5 -= 90;

  Serial.print('a');
  Serial.print(temp_servo0);
  Serial.print('b');
  Serial.print(temp_servo1);
  Serial.print('c');
  Serial.print(temp_servo2);
  Serial.print('d');
  Serial.print(temp_servo3);
  Serial.print('e');
  Serial.print(temp_servo4);
  Serial.print('f');
  Serial.print(temp_servo5);
  Serial.println('g');
}

/*
  Description: Function for move robot arm through serial port  
  Argument
    char command:  command to run one of 6 servos
    byte angle: servo angle  
*/
void move_robot_serial(char command, byte angle){
  int i = 0;
  Serial.println("program robot serial");
  switch(command){
    /*--------------------- servo 0 ---------------------*/ 
    case 'a':  
    {

    }
    break;
    /*--------------------- servo 1 ---------------------*/ 
    case 'b': 
    {

    }
    break;
    /*--------------------- servo 2 ---------------------*/ 
    case 'c': 
    {

    }
    break;
    /*--------------------- servo 3 ---------------------*/ 
    case 'd': 
    {

    }
    break;
    /*--------------------- servo 4 ---------------------*/ 
    case 'e': 
    {

    }
    break;
    /*--------------------- servo 5 ---------------------*/ 
    case 'f': 
    {

    }
    break;
   
    default:
    break;
  }
}

/*
  Description: Function for save robot arm current position 
*/
void save_robot(){

}

/*
  Description: Function for reset robot arm
*/
void reset_robot(){
  run_robot_flag = false;
  reset_arm_position(); 
}

/*
  Description: Function for running robot arm with pre-saved route
*/
void run_robot(){
  
  while(run_robot_flag == true){
    //Serial.println("run robot");
    if(radio.available()){ 
      radio.read(&rf_rx_buffer, sizeof(rf_rx_buffer));
      if(rf_rx_buffer[0] == 0x03){
        run_robot_flag = false;
        Serial.println("halt run robot");
      }
    }
    if(Serial.available()){
      char inCommand = Serial.read();
      if(inCommand == '3'){ // reset robot  
        //Serial.println("serial - reset robot");
        run_robot_flag = false;
        reset_robot();
      }
    }
    //Serial.println(run_robot_flag);
    move__robot();
  }
}

/*============================= aeduino functions ===========================*/ 

void setup() {

  // radio setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  
 
  // serial setup
  Serial.begin(9600);
  Serial.println("cobit robot arm controller v1.0");

  // start radio 
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening(); 

  // Servo setup 
  bas_servo.attach(2);
  shl_servo.attach(3);
  elb_servo.attach(4);
  wri_servo.attach(5);
  wro_servo.attach(6);
  gri_servo.attach(9);

  // robot home position 
  reset_arm_position();
  
  delay(2000);
}

void loop() {

  char inCommand;
  int intCommand;

  // radio input 
  if (radio.available()) {
    radio.read(&rf_rx_buffer, sizeof(rf_rx_buffer));

    // reset robot 
    if(rf_rx_buffer[0] == RESET_ROBOT){
      run_robot_flag = false;
      reset_robot();

    // move robot 
    }else if(rf_rx_buffer[0] == MOVE_ROBOT){
      if(run_robot_flag == false){
        move_robot();
      }
    }
  }
 
  // serial input 
  String inString = "";
  if(Serial.available()>0){
    if(Serial.available()){
      inString = Serial.readStringUntil('\n');
    } 
    inCommand = inString[0];
    intCommand = inCommand - 0x30;
    Serial.println(intCommand);

    // run robot  
    if(intCommand == RUN_ROBOT){ 
      if(run_robot_flag == false){
        run_robot();
      }    

    // reset robot 
    }else if(intCommand == RESET_ROBOT){   
      run_robot_flag = false;
      reset_robot();

    // move robot 
    }else if(intCommand == MOVE_ROBOT){   
/*      Serial.println(inString);
      // angle 0
      int first = 1;
      int second = inString.indexOf('b');
      String angle_0_str = inString.substring(first+1, second);
      servo00SP = angle_0_str.toInt();
      Serial.println(servo00SP);
      // angle 1
      first = inString.indexOf('b');
      second = inString.indexOf('c');
      String angle_1_str = inString.substring(first+1, second);
      servo01SP = angle_1_str.toInt();
      Serial.println(servo01SP);
      // angle 2
      first = inString.indexOf('c');
      second = inString.indexOf('d');
      String angle_2_str = inString.substring(first+1, second);
      servo02SP = angle_2_str.toInt();
      Serial.println(servo02SP);
      // angle 3
      first = inString.indexOf('d');
      second = inString.indexOf('e');
      String angle_3_str = inString.substring(first+1, second);
      servo03SP = angle_3_str.toInt();
      Serial.println(servo03SP);
      // angle 4
      first = inString.indexOf('e');
      second = inString.indexOf('f');
      String angle_4_str = inString.substring(first+1, second);
      servo04SP = angle_4_str.toInt();
      Serial.println(servo04SP);
      // angle 5
      first = inString.indexOf('f');
      second = inString.indexOf('g');
      String angle_5_str = inString.substring(first+1, second);
      servo05SP = angle_5_str.toInt();
      Serial.println(servo05SP);
      move__robot();
    }else{
      String inSubStr = inString.substring(1, (inString.length()));
      Serial.println(inSubStr);
      int angle = inSubStr.toInt();
      move_robot_serial(inCommand, angle);*/
    }
  }

  if(run_robot_flag == true){
    run_robot();
  }
}
