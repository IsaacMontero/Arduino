/*
AT+CWMODE=3
AT+CWJAP="MOVISTAR_21D0","HAzE993Cv4PAX4CE4H44"
AT+CIPMUX=1
AT+CIPSERVER=1,80
AT+CIPSTA="192.168.1.110"
(IP:) AT+CIFSR
*/

#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial BT1(3, 2); // RX | TX

void setup()
  {  Serial.begin(9600);
     BT1.begin(9600);
     Wire.begin(); 
  }

void loop()
  {  String B= "." ;
     while (BT1.available())
         { char c = BT1.read() ;
           Serial.print(c);
           B += c;
         }
           Wire.beginTransmission(2);
           Wire.write(B.c_str()); 
           Wire.endTransmission();
     if (Serial.available())
         {  char c = Serial.read();
            BT1.print(c);
         }
   }
