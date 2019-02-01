#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "mini-estaciones.firebaseio.com"
#define FIREBASE_AUTH "OMzfBCUGafSScajKAUIu9XXCjBBYm3RHe2Dlc66m"
#define WIFI_SSID "vodafoneN1D0"
#define WIFI_PASSWORD "oras.clCo3"

SoftwareSerial NodeMCU(D2, D3);
String LocationName;
 
void setup() {
  Serial.begin(9600);
  NodeMCU.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
 
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(WIFI_SSID);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.print("Connecting");
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed()) {
  Serial.println(Firebase.error());
}
}
void firebasereconnect(){
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop() {
  Serial.print("Reading from firebase : ");
  //FirebaseObject alcohol = Firebase.get("/core-box/-LWDVtlsmR0vtMgQDJbH/alcohol");
  Firebase.setFloat("test", 123);
  String alcoholDescription = Firebase.getString("/core-box/-LWDVtlsmR0vtMgQDJbH/alcohol/descripcion");
  Serial.println(alcoholDescription);
  NodeMCU.print(alcoholDescription);
  NodeMCU.print("\n");
  delay(10000);}

