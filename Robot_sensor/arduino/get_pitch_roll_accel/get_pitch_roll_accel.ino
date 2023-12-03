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