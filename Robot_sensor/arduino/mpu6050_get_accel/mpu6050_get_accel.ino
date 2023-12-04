/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

unsigned long timer = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
}

void loop() {
  mpu.update();

  if(millis() - timer > 200){ // print data every second
    print_angle();
    timer = millis();
  }

}

void print_angle(){
  Serial.print("X: ");
  Serial.print(mpu.getAccX());
  Serial.print("Y: ");
  Serial.print(mpu.getAccY());
  Serial.print("Z: ");
  Serial.println(mpu.getAccZ());
}
