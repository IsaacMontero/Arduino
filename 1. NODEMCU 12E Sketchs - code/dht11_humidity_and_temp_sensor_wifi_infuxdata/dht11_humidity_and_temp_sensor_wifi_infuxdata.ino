#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <DHT11.h>

DHT11 dht11(2);
  
const char* ssid   = "vodafoneN1D0";  //  your network SSID (name)
const char* pass = "oras.clCo3";      // your network password
int status = WL_IDLE_STATUS;          // the Wifi radio's status

// the IP address of your InfluxDB host
IPAddress host(192, 168, 0, 200);
// the HostName of your InfluxDB host
const char* onlineHost = "kirometep.ddns.net";

// the port that the InfluxDB UDP plugin is listening on
int port = 8888;

WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  //note DHT11 need 1 sec to get data
  delay(1000);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to a:\t");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print('.');
  }

  Serial.println("Connected to network");
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

//  Gestión de la conexión
//  WiFi.reconnect();
//  WiFi.disconnect(true);
//  WiFi.isConnected();
//  WiFi.setAutoConnect(autoConnect);
//  WiFi.status();
//   
//  Devuelven el valor indicado (no sirven para reescribir el valor)
//  WiFi.SSID();
//  WiFi.hostname();
//  WiFi.localIP();
//  WiFi.subnetMask()
//  WiFi.gatewayIP();
//  WiFi.dnsIP(dns_no);
//  WiFi.macAddress();
}

void sendUdpPacket(String line){
  // send the packet
    Serial.println("Sending UDP packet...");
    if(udp.beginPacket(host, port) == 1) {
      udp.print(line);
      if(udp.endPacket() == 1) Serial.println("endPacket local ok");
      else Serial.println("endPacket local fail");
    } else if(udp.beginPacket(onlineHost, port) == 1) {
      udp.print(line);
      if(udp.endPacket() == 1) Serial.println("endPacket online ok");
      else Serial.println("endPacket online fail");
    }
    else{
      Serial.println("beginPacket fail");
    }
}


void loop() {
  String line;
  float temperature, humidity;
  
  // wait 1 second
  delay(1000);

  // get the current temperature from the sensor, to 2 decimal places
  if(dht11.read(humidity, temperature) == 0){
    // concatenate the temperature into the line protocol
    line = String("temperature,Station=S1 value=");
    line += temperature;
    Serial.println(line);
    sendUdpPacket(line);

    line = String("humidity,Station=S1 value=");
    line += humidity;
    Serial.println(line);
    sendUdpPacket(line);
  }
  Serial.println();
}
