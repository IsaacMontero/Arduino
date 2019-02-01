/*
AT+CWMODE=3
AT+CWJAP="MOVISTAR_21D0","HAzE993Cv4PAX4CE4H44"
AT+CIPMUX=1
AT+CIPSERVER=1,80
AT+CIPSTA="192.168.1.110"
(IP:) AT+CIFSR
*/

#include <SoftwareSerial.h>
SoftwareSerial wifi(3, 2); // RX | TX

void setup()
  {  Serial.begin(9600);
     wifi.begin(9600);
  }

void loop()
  {  String B= "." ;
     while (wifi.available())
         { char c = wifi.read() ;
           Serial.print(c);
         }
     if (Serial.available())
         {  char c = Serial.read();
            wifi.print(c);
         }
   }
