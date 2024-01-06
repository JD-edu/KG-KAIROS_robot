/*
MIT License

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

#include <MPU6050_light.h>
#include <math.h>

MPU6050 mpu(Wire);

float accelX, accelY, accelZ;
float pitch, roll;


unsigned long timer = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

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
        print_pitch_roll();
        timer = millis();
    }

}

void print_pitch_roll() {
    accelX = mpu.getAccX();
    accelY = mpu.getAccY();
    accelZ = mpu.getAccZ();

    // Calculate the pitch and roll angles
    calculateAngles();

    Serial.print("Low Pitch Roll: ");
    Serial.print(pitch, 2);
    Serial.print(", ");
    Serial.print(roll, 2);
    Serial.print(" lib Pitch Roll: ");
    Serial.print(mpu.getAccAngleY(), 2);
    Serial.print(", ");
    Serial.println(mpu.getAccAngleX(), 2);
}

void calculateAngles() {
  // Calculate the pitch angle
  pitch = atan2(accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / M_PI;

  // Calculate the roll angle
  roll = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ)) * 180.0 / M_PI;
}