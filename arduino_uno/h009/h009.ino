#include <SoftwareSerial.h>
#include <DHT.h>

#define blueTX  2
#define blueRX  3
#define DHTPIN  4
#define DHTTYPE DHT11

SoftwareSerial HC06(blueTX, blueRX);
DHT dht(DHTPIN, DHTTYPE);

char ser = 0;
char ble = 0;
float temp = 0;
float humi = 0;

void setup(){
  Serial.begin(9600);
  HC06.begin(9600);  
  dht.begin();
}

void HC06proc(){
   if(Serial.available()>0){
    ser = Serial.read();
    HC06.write(ser);
  }
    
  if(HC06.available()>0){
    ble = HC06.read();
    Serial.write(ble);
  }
}
void DHTproc(){
  temp = dht.readTemperature(); // 온도측정.
  humi = dht.readHumidity();    // 습도 측정
 
  if (isnan(temp) || isnan(humi)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}    

void DataPrint(){
  Serial.print("Tem:");
  Serial.print(temp);
  Serial.print(" ℃");
  Serial.print('\t');
  Serial.print("Hum:");
  Serial.print(humi);
  Serial.println(" ％");
  
  HC06.print("Tem:");
  HC06.print(temp);
  HC06.print(" ℃");
  HC06.print('\t');
  HC06.print("Hum:");
  HC06.print(humi);
  HC06.print(" ％");
}

void loop(){
  HC06proc();
  DHTproc();
  DataPrint();
  delay(2000);
}
