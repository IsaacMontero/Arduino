#include <SoftwareSerial.h>
#include <Servo.h>                    // Incluir la librería Servo

Servo servo1;                         // Crear un objeto tipo Servo llamado servo1
int angulo = 0 ;
#define DEBUG true
String W =" ";
char c;
String value = "";
int analog_value = 0;
int buff = 12;
int i=0;

SoftwareSerial wifi(5,4); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  wifi.begin(9600); // your esp's baud rate might be different
  
  sendCommand("AT+RST\r\n",500,DEBUG); // reset module
  sendCommand("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
  sendCommand("AT+CWJAP=\"vodafone7478\",\"E4TYM3GDLHZMTU\"\r\n",3000,DEBUG);
  delay(3000);
  sendCommand("AT+CIPSTA=\"192.168.0.160\"\r\n",1000,DEBUG); // set ip address
  delay(1000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  delay(1000);
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  delay(1000);
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  
  servo1.attach(9) ; // Conectar servo1 al pin 8
}
    
void loop()
{

     while (wifi.available())
         { c = wifi.read() ;
           //Serial.print(c);
           W = W + c ;
           //delay(500);
         }
   
     if ( c == '\n' or i>buff)                     // Sin han pulsado intro
         { if ( W.indexOf("<AccY:") > 0 )    // Comprobamos si P13 esta incluido en el string
               { 
                   value = W.substring(W.lastIndexOf("<AccY:")+7, W.lastIndexOf("<AccY:")+12);
                   String sign = W.substring(W.lastIndexOf("<AccY:")+6, W.lastIndexOf("<AccY:")+7);
                   if(value.substring(0,2) == "00" && (sign=="+" || sign=="-") ){
                       //Serial.println("Y: " + value);
                       if(isNumeric(value)){
                           analog_value = value.toInt();
                           if(sign == "-" ){
                                analog_value = (1000-analog_value) * 10;
                           }else{
                               analog_value = (analog_value+1000) * 10;
                           }
                           
                           angulo  = map( analog_value, 0, 20000, 0, 180);
                           //Serial.println(analog_value);
                           Serial.println(angulo);
                           servo1.write(angulo);
                     }
                   }
               }
           W = "" ;  c = ' ' ; value = ""; analog_value = 0; i=0;
           // Limpiamos las variables
         }
      i++;
}

// check a string to see if it is numeric
bool isNumeric(String str) {
    for(char i = 0; i < str.length(); i++) {
        if ( !(isDigit(str.charAt(i)) || str.charAt(i) == '.' )) {
            return false;
        }
    }
    return true;
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
