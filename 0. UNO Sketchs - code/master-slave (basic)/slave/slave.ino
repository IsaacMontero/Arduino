#include <Wire.h>

int pin;
String estado;
void setup()
{
  pinMode(13, OUTPUT);
  Wire.begin(2);              
  Wire.onReceive(receiveEvent); 

  Serial.begin(9600);
}

void loop()
{ 
}

void receiveEvent(int howMany)
{
   char buf;
   String msg = "";
   while(Wire.available()) // slave may send less than requested
  { 
     buf = Wire.read();
     msg += buf;
  }
   Serial.println( howMany ); //Al salir imprimir el mensaje
   Serial.println( msg ); //Al salir imprimir el mensaje
}
