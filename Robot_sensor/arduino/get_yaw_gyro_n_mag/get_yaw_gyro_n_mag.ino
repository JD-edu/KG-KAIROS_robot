#include "MPU9250.h"
#include <math.h>

MPU9250 mpu;

float magX, magY, magZ;
float gyroX, gyroY, gyroZ;
float yaw;

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
    magX = mpu.getMagX();
    magY = mpu.getMagY();
    magZ = mpu.getMagZ();
    gyroX = mpu.getGyroX();
    gyroY = mpu.getGyroY();
    gyroZ = mpu.getGyroZ();

    // Calculate the pitch and roll angles
    yaw = get_yaw_from_gyro_and_magnetic(gyroZ, magX, magY, magZ) ;

    Serial.print("Low yaw: ");
    Serial.print(yaw, 2);
    Serial.print(", ");
    Serial.print(" lib yaw: ");
    Serial.println(mpu.getYaw(), 2);
   
}

float get_yaw_from_gyro_and_magnetic(float gyro_z, float magnetic_x, float magnetic_y, float magnetic_z) {
  // Calculate the pitch angle using the accelerometer.
  float pitch = atan2(-magnetic_y, sqrt(magnetic_x * magnetic_x + magnetic_z * magnetic_z));

  // Calculate the yaw angle using the gyro and the pitch angle.
  float yaw = gyro_z * (M_PI / 180) * 0.001; // Convert gyro rate from degrees per second to radians per second.
  yaw += pitch;

  // Normalize the yaw angle to the range [0, 2 * M_PI].
  if (yaw < 0) {
    yaw += 2 * M_PI;
  } else if (yaw > 2 * M_PI) {
    yaw -= 2 * M_PI;
  }

  return yaw;
}
