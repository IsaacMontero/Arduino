#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DEBUG true

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

SoftwareSerial wifi(3,2); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  wifi.begin(9600); // your esp's baud rate might be different
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines and turn on backlight
  
  lcd.setCursor(3,0); //Start at character 4 on line 0
  lcd.print("ESP8266 Server");
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
   
  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  sendCommand("AT+CWJAP=\"vodafoneN1D0\",\"oras.clCo3\"\r\n",3000,DEBUG);
  delay(1000);
  sendCommand("AT+CIPSTA=\"192.168.0.160\"\r\n",1000,DEBUG); // set ip address
  delay(1000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  delay(1000);
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  delay(1000);
  sendCommand("AT+CIPSERVER=1,81\r\n",1000,DEBUG); // turn on server on port 80

  lcd.setCursor(0,1);
  lcd.print("Server Ready:");
  Serial.println("Server Ready");
}
 
void loop()
{
  int lcd_line = 0; // using lines 1,2 and 3
 
}


/*
* Name: sendCommand
* Description: Function used to send data to wifi.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the wifi (if there is a reponse)
*/
String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
    wifi.print(command); // send the read character to the wifi
    long int time = millis();
    while( (time+timeout) > millis())
    {
      while(wifi.available())
      {
        // The esp has data so display its output to the serial window 
        char c = wifi.read(); // read the next character.
        response+=c;
      }  
    }
    if(debug)
    {
      Serial.print(response);
    }
    return response;
}
