#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

int pin = 2;
int pinOut = 16;
DHT11 dht11(pin);

void setup()
{
pinMode(pinOut, OUTPUT);
Serial.begin(9600);
delay(1000);
Serial.print("Ready: ");

Serial.println("OFF");
digitalWrite(pinOut,HIGH);
}


 void loop()
{
 int err;
 float temp, hum;
 if ((err = dht11.read(hum, temp)) == 0) // Si devuelve 0 es que ha leido bien
 {

  if(hum>=40)
  {
    Serial.println("ON");
    digitalWrite(pinOut,LOW);
  } else {
    Serial.println("OFF");
    digitalWrite(pinOut,HIGH);
  }
  
 Serial.print("Temp: ");
 Serial.print(String(temp));
 Serial.println("ºC");
 Serial.print("Hum:");
 Serial.print(String(hum));
 Serial.println("%");
 Serial.println();
 }
 else
 {
 Serial.print("Error Num :");
 Serial.println(String(err));
 }
 delay(500); 
}
