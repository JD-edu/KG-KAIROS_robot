#include "MPU9250.h"
#include <math.h>

MPU9250 mpu;

float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;
float pitch, roll;

// Complementary filter coefficients
float alpha = 0.95f;
float beta = 1.0f - alpha;

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

// Calculate the pitch and roll angles from the gyro and accelerometer readings
void calculateAngles() {
  // Calculate the delta pitch and roll angles
  float deltaPitch = gyroX * alpha;
  float deltaRoll = gyroY * alpha;

  // Calculate the pitch and roll angles
  pitch += deltaPitch;
  roll += deltaRoll;

  // Compensate for the effects of acceleration on the pitch and roll angles
  float accelPitch = atan2(accelX, sqrt(accelY * accelY + accelZ * accelZ));
  float accelRoll = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ));

  pitch = beta * pitch + alpha * accelPitch;
  roll = beta * roll + alpha * accelRoll;
}
