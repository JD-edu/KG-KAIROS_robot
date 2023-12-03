#include <MPU6050_light.h>
#include <math.h>

MPU6050 mpu(Wire);

float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;
float pitch, roll;

// Complementary filter coefficients
float alpha = 0.95f;
float beta = 1.0f - alpha;

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
    Serial.print(mpu.getAngleX(), 2);
    Serial.print(", ");
    Serial.println(mpu.getAngleY(), 2);
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
