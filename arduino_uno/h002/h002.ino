#include <DHT11.h>

DHT11 dht11(2);

void setup(){
    Serial.begin(115200);
}

void loop(){   
    int temperature = dht11.readTemperature();
    int humidity = dht11.readHumidity();  
    if (isnan(temperature) || isnan(humidity)){
      Serial.println("Fail to read from DHT sensor!");
      return;
    }
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  
    delay(1000);
}
