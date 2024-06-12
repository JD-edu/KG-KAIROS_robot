void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

String inString = "";

int a = 0, b = 0, c = 0, d = 0;
String a_str, b_str, c_str, d_str;

void loop() {
  if (Serial.available() > 0){  
    // a
    inString = Serial.readStringUntil('\n');
    int first = inString.indexOf('a');
    int second = inString.indexOf('b');
    a_str = inString.substring(first+1, second);
    a = a_str.toInt();    
    Serial.print(a);
    Serial.print(" ");
    // b
    first = inString.indexOf('b');
    second = inString.indexOf('c');
    b_str = inString.substring(first+1, second);
    b = b_str.toInt();
    Serial.print(b);
    Serial.print(" ");
    // c
    first = inString.indexOf('c');
    second = inString.indexOf('d');
    c_str = inString.substring(first+1, second);
    c = c_str.toInt();
    Serial.print(c);
    Serial.print(" ");
    // d
    first = inString.indexOf('d');
    second = inString.indexOf('e');
    d_str = inString.substring(first+1, second);
    d = d_str.toInt();
    Serial.print(d);
    Serial.println(" ");
  }
}
