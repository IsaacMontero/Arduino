#include <Wire.h>

void setup()
{
  Wire.begin(); 
  pinMode(13, OUTPUT);
}

String data;
char buf[10];

void loop()
{
data = "Test A";
Wire.beginTransmission(2);
data.toCharArray(buf, 10);
Wire.write(buf); 
Wire.endTransmission();
//digitalWrite(13, data);
delay(500);
data = "Test B";
Wire.beginTransmission(2);
data.toCharArray(buf, 10);
Wire.write(buf); 
Wire.endTransmission();
//digitalWritealgo data);
delay(500);
}

