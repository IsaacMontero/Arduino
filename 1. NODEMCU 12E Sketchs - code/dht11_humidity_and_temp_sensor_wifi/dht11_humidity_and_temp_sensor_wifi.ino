#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

int pin = 2;
DHT11 dht11(pin);

const char* ssid = "vodafoneN1D0"; //Nombre de la red WiFi a la que nos vamos a conectar
const char* password = "oras.clCo3"; //Contrasena de la red WiFi a la que nos vamos a conectar

void setup()
{
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
delay(1000);
Serial.print("Ready: ");

 /*Mostrar red en pantala*/
 Serial.print("Connecting to:");
 Serial.println(ssid);
 Serial.print("Connecting to:");
 Serial.println( ssid);

 /*Conectarnos a la red WiFi*/
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 /*Mostrar nuestra IP*/
 String ip = WiFi.localIP().toString();
 Serial.print("Red: ");
 Serial.println(ssid);
 Serial.print("IP address:");
 Serial.println(ip);
 }
}


 void loop()
{
 int err;
 float temp, hum;
 if ((err = dht11.read(hum, temp)) == 0) // Si devuelve 0 es que ha leido bien
 {

 Serial.print("Temp: ");
 Serial.print(String(temp));
 Serial.println("ºC");
 Serial.print("Hum:");
 Serial.print(String(hum));
 Serial.println("%");
 }
 else
 {
 Serial.print("Error Num :");
 Serial.println(String(err));
 }
 delay(3000); 
 /*Mostrar nuestra IP*/
 String ip = WiFi.localIP().toString();
 Serial.print("Red: ");
 Serial.println(ssid);
 Serial.print("IP address:");
 Serial.println(ip);
 delay (3000);
}
