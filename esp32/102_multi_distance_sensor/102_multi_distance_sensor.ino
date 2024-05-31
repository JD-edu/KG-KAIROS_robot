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
#include "Adafruit_VL53L0X.h"

// set the pins to shutdown
#define SHT_LOX1 32
#define SHT_LOX2 33
#define SHT_LOX3 3
#define SHT_LOX4 19

#define LOX1_ADDRESS 0x40
#define LOX2_ADDRESS 0x41
#define LOX3_ADDRESS 0x42
#define LOX4_ADDRESS 0x43

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// Sensor variables
int sensor1,sensor2, sensor3, sensor4;

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;

void read_multi_sensors() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  if(measure1.RangeStatus != 4) {     // if not out of range
    sensor1 = measure1.RangeMilliMeter;    
    //Serial.println(sensor1);
  } 

  // print sensor two reading
  if(measure2.RangeStatus != 4) {
    sensor2 = measure2.RangeMilliMeter;
    //Serial.println(sensor2);
  }

  // print sensor three reading
  if(measure3.RangeStatus != 4) {
    sensor3 = measure3.RangeMilliMeter;
    //Serial.println(sensor3);
  }

  // print sensor four reading
  if(measure3.RangeStatus != 4) {
    sensor4 = measure4.RangeMilliMeter;
    //Serial.println(sensor3);
  } 
}

void distance_sensor_setup() {

  Serial.println("VL53L0X: setup...");
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);

  Serial.println("VL53L0X: Both in reset mode...(pins are low)");

  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // 1 센서 활성화, 2/3/4 센서 비활성화 
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);

  // 1 센서 주소 할당하기. 1 센서가 반응하지 않으면 계속 시도하기  
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1){
      if(!lox1.begin(LOX1_ADDRESS)){
        break;
      }
    }
  }
  
  // 2 센서 주소 할당하기, 2 센서가 반응하지 않으면 계속 시도학 ㅣ
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1){
      if(!lox2.begin(LOX2_ADDRESS)){
        break;
      }
    }
  }

  // 3 센서 주소 할당하기, 3 센서가 반응하지 않으면 계속 시도학 ㅣ
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1){
       if(!lox3.begin(LOX3_ADDRESS)){
        break;
      }
    }
  }

  // 4 센서 주소 할당하기, 4 센서가 반응하지 않으면 계속 시도학 ㅣ
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);
  //initing LOX4
  if(!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1){
      if(!lox3.begin(LOX3_ADDRESS)){
        break;
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.print("ACT ground robot Start...");
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  distance_sensor_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  read_multi_sensors();
  Serial.print(sensor1);
  Serial.print(" ");
  Serial.print(sensor2);
  Serial.print(" ");
  Serial.print(sensor3);
  Serial.print(" ");
  Serial.print(sensor4);
  Serial.println(" ");
  delay(100);
}
