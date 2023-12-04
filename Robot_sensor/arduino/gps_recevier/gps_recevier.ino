#include <SoftwareSerial.h>

SoftwareSerial gps(11, 12)

void setup() {
  // put your setup code here, to run once:
  Serila.begin(9600);
  gps.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(gps.available()){
    Serial.write(gps.read());
  }
}
