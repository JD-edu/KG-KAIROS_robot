/*MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/
#include <WiFi.h>
#include <WebServer.h>

#define M1_B    26
#define M1_A    27

#define FORWARD   1
#define BACKWARD  2
#define STOP      3

/* Put your SSID & Password */
const char* ssid = "SK_WiFiGIGA73BA_2.4G";  // Enter SSID here
const char* password = "1609043407";  //Enter Password here

int motor_status = STOP;

WebServer server(80);

void go_forward(){
  Serial.println("forward");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
}

void go_backward(){
  Serial.println("backward");
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, LOW);
  delay(200);
}

void setup() {
  Serial.begin(115200);

  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  stop();

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  
  server.on("/", handle_OnConnect);
  server.on("/forward", handle_forward);
  server.on("/backward", handle_backward);
  server.on("/stop", handle_stop);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  
}

void handle_OnConnect() {
  stop();
  Serial.println("motor stop");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_forward() {
  go_forward();
  motor_status = FORWARD;
  Serial.println("motor forward");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_backward() {
  go_backward();
  motor_status = BACKWARD;
  Serial.println("motor backward");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_stop() {
  stop();
  motor_status = STOP;
  Serial.println("motor stop");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t motor_status){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Station Mode</h3>\n";

  switch(motor_status){
    case 1:
      {ptr +="<p>Motor forward</p><a class=\"button button-on\" href=\"/forward\">ON</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-off\" href=\"/backward\">OFF</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-off\" href=\"/stop\">OFF</a>\n";}
      break;
    case 2:
      {ptr +="<p>Motor forward</p><a class=\"button button-off\" href=\"/forward\">OFF</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-on\" href=\"/backward\">ON</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-off\" href=\"/stop\">OFF</a>\n";}
      break;
    case 3:
      {ptr +="<p>Motor forward</p><a class=\"button button-off\" href=\"/forward\">OFF</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-off\" href=\"/backward\">OFF</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-on\" href=\"/stop\">ON</a>\n";}
      break;
  }
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}