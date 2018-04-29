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

  if(wifi.available()) // check if the esp is sending a message 
  {

    if(wifi.find("WOL"))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = wifi.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
    sendCommand("AT+CIPSTART=4,\"UDP\",\"192.168.0.255\",9,9,0\r\n",1000,DEBUG);
    for(int i = 0; i<10; i++) {
      sendCommand("AT+CIPSEND=4,102\r\n",1000,DEBUG); // Send 102 bytes to transmission num.4
      sendMagicPacket(1000,DEBUG);
      delay(1000);
    
      lcd.setCursor(0,2);
      lcd.print("Magic packet sent: ");
      lcd.print(i+1);
    }
    
    String content = "Magic Packet Sent!";
    
    sendHTTPResponse(connectionId,content);
    
    // make close command
    String closeCommand = "AT+CIPCLOSE="; 
    closeCommand+=connectionId; // append connection id
    closeCommand+="\r\n";
     
    sendCommand(closeCommand,1000,DEBUG); // close connection
    }
  }
}

void sendMagicPacket(const int timeout, boolean debug){
  
  String response = "";
  byte magic_packet[144] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  byte mac[6] = { 0x00, 0x24, 0x1D, 0xD6, 0x2F, 0x58 };
  
  for (byte i = 6; i < 144; i++)
  {
    magic_packet[i] = mac[i%6];
  }
  
  for (byte i = 0; i < 144; i++)
  {
    wifi.write(magic_packet[i]); // send the read character to the wifi
  } 
  
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
 
/*
* Name: sendData
* Description: Function used to send data to wifi.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the wifi (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);
           
    wifi.write(data,dataSize); // send the read character to the wifi
    if(debug)
    {
      Serial.println("\r\n====== HTTP Response From Arduino ======");
      Serial.write(data,dataSize);
      Serial.println("\r\n========================================");
    }
    
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
 
/*
* Name: sendHTTPResponse
* Description: Function that sends HTTP 200, HTML UTF-8 response
*/
void sendHTTPResponse(int connectionId, String content)
{
     
     // build HTTP response
     String httpResponse;
     String httpHeader;
     // HTTP Header
     httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"; 
     httpHeader += "Content-Length: ";
     httpHeader += content.length();
     httpHeader += "\r\n";
     httpHeader +="Connection: close\r\n\r\n";
     httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
     sendCIPData(connectionId,httpResponse);
}
 
/*
* Name: sendCIPDATA
* Description: sends a CIPSEND=<connectionId>,<data> command
*
*/
void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommand(cipSend,1000,DEBUG);
   sendData(data,1000,DEBUG);
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
