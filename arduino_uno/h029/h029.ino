#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update(); 
  Serial.print("x : ");
  Serial.print(mpu6050.getAccX());
  Serial.print("\ty : ");
  Serial.print(mpu6050.getAccY());
  Serial.print("\tz : ");
  Serial.println(mpu6050.getAccZ());

}
