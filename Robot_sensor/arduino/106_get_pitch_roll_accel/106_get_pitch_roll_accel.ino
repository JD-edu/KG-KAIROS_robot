#include "MPU9250.h"
#include <math.h>

MPU9250 mpu;

float accelX, accelY, accelZ;
float pitch, roll;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 250) {
            print_pitch_roll();
            prev_ms = millis();
        }
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
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
}

void calculateAngles() {
  // Calculate the pitch angle
  pitch = atan2(accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / M_PI;

  // Calculate the roll angle
  roll = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ)) * 180.0 / M_PI;
}