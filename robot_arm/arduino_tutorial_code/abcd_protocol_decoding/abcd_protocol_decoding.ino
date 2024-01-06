int baseAngle = 90;
int shoulderAngle = 90;
int upperarmAngle = 90;
int forearmAngle = 90;

String baseAngle_str;
String shoulder_str;
String upperarm_str;
String forearm_str;
String inString;

void setup() {
   Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    inString = Serial.readStringUntil('\n');
    int first = inString.indexOf('a');
    int second = inString.indexOf('b');
    baseAngle_str = inString.substring(first+1, second);
    baseAngle = baseAngle_str.toInt();    
    Serial.print(baseAngle);
    Serial.print(" ");
    // angle 1
    first = inString.indexOf('b');
    second = inString.indexOf('c');
    shoulder_str = inString.substring(first+1, second);
    shoulderAngle = shoulder_str.toInt();
    Serial.print(shoulderAngle);
    Serial.print(" ");
    // angle 2
    first = inString.indexOf('c');
    second = inString.indexOf('d');
    upperarm_str = inString.substring(first+1, second);
    upperarmAngle = upperarm_str.toInt();
    Serial.println(" ");
    Serial.print(upperarmAngle);
    // angle 3
    first = inString.indexOf('d');
    second = inString.indexOf('e');
    forearm_str = inString.substring(first+1, second);
    forearmAngle = forearm_str.toInt();
    Serial.print(forearmAngle);
    Serial.println(" ");
  }
}
