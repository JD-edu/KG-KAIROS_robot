#include <SoftwareSerial.h>
// Using softserial as debugging. Arduino Uno has only 1 serial port. 
SoftwareSerial Serial2(7,8);

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.println("Start...");
}

long data = 0;  // 4 bytes       

void loop(){ 

  data += 100;
  Serial2.print( "data:" );    // print for debugging 
  Serial2.print( data );
 
  byte data_buffer[6] = {0};   // Command packer container 
  data_buffer[0] = 0xf5;
  data_buffer[1] = 4;
  data_buffer[2] = (data >> 24) & 0xff;     // long 4 bytes as byte array 
  data_buffer[3] = (data >> 16) & 0xff;    
  data_buffer[4] = (data >> 8) & 0xff;
  data_buffer[5] = data & 0xff;
 
  Serial.write(data_buffer, 5);  // Sending command packets 
  delay(1000);

}