// Version 2.1.0 - Development

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DEBUG true

DHT dht;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

SoftwareSerial wifi(13,12); // make RX Arduino line is pin 12, make TX Arduino line is pin 3.
                            // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                            // and the RX line from the esp to the Arduino's pin 13
                             
void setup()
{
  Serial.begin(9600);
  
  wifi.begin(9600); // your esp's baud rate might be different
  lcd.begin(16,2);  // initialize the lcd for 20 chars 4 lines and turn on backlight
  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("ESP8266 Server");
  
  dht.setup(2);       // DHT - Negro
  pinMode(3, INPUT);  // 135 - Marrón
  pinMode(4, INPUT);  // MQ2 - Rojo
  pinMode(5, INPUT);  // MQ3 - Naranja
  pinMode(6, INPUT);  // MQ4 - Amarillo
  pinMode(7, INPUT);  // MQ5 - Verde
  pinMode(8, INPUT);  // MQ6 - Azul
  pinMode(9, INPUT);  // MQ7 - Morado
  pinMode(10, INPUT); // MQ8 - Gris
  pinMode(13, INPUT); // MQ9 - Blanco

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

  lcd.setCursor(0,0);
  lcd.print("ESP8266 Ready:");
  Serial.println("Server Ready");
}

void loop()
{
  // Ritmo Refresco;
  delay(1000);

  // DHT22 y AM2302 Negro
  float humedad = dht.getHumidity();
  float temperatura = dht.getTemperature();
  
  // MQ135 Marron
  int mq135_adc = analogRead(A3);
  float mq135_voltaje = mq135_adc * (5.0 / 1023.0);
  float mq135_resistencia = 1000*((5-mq135_voltaje)/mq135_voltaje);
  double dioxidoDeCarbono = 245*pow(mq135_resistencia/5463, -2.26);
  double oxidosDeNitrogeno = 132.6*pow(mq135_resistencia/5463, -2.74);
  double amoniaco = 161.7*pow(mq135_resistencia/5463, -2.26);
  String mq135_umbral = "false";

  if(digitalRead(5) == 0){
    mq135_umbral = "true";
  }
  
  // MQ2 Rojo
  int mq2_adc = analogRead(A4);
  float mq2_voltaje = mq2_adc * (5.0 / 1023.0);
  float mq2_resistencia = 1000*((5-mq2_voltaje)/mq2_voltaje);
  double glp = 8555*pow(mq2_resistencia/5463, -1.74);
  bool mq2_umbral = digitalRead(13); 

  // MQ3 Naranja
  int mq3_adc = analogRead(A5);
  float mq3_voltaje = mq3_adc * (5.0 / 1023.0);
  float mq3_resistencia = 1000*((5-mq3_voltaje)/mq3_voltaje); 
  double alcohol = 1.108*pow(mq3_resistencia/5463, -1.41);
  String mq3_umbral = "false";

  if(digitalRead(12) == 0){
    mq3_umbral = "true";
  }

  // MQ4 Amarillo
  int mq4_adc = analogRead(A6);
  float mq4_voltaje = mq4_adc * (5.0 / 1023.0);
  float mq4_resistencia = 1000*((5-mq4_voltaje)/mq4_voltaje);
  double metano = 6922*pow(mq4_resistencia/5463, -1.91);
  String mq4_umbral = "false";

  if(digitalRead(11) == 0){
    mq4_umbral = "true";
  }

  // MQ5 Verde
  // -- TODO --

  // MQ6 Azul
  int mq6_adc = analogRead(A8);
  float mq6_voltaje = mq6_adc * (5.0 / 1023.0);
  float mq6_resistencia = 1000*((5-mq6_voltaje)/mq6_voltaje);
  double propano = 2738*pow(mq6_resistencia/5463, -1.81);
  String mq6_umbral = "false";

  if(digitalRead(9) == 0){
    mq6_umbral = "true";
  }

  // MQ7 Morado
  int mq7_adc = analogRead(A9);
  float mq7_voltaje = mq7_adc * (5.0 / 1023.0);
  float mq7_resistencia = 1000*((5-mq7_voltaje)/mq7_voltaje);
  double monoxidoDeCarbono = 233.9*pow(mq7_resistencia/5463, -1.40);
  String mq7_umbral = "false";

  if(digitalRead(8) == 0){
    mq7_umbral = "true";
  }

  // MQ8 Gris
  int mq8_adc = analogRead(A7);
  float mq8_voltaje = mq8_adc * (5.0 / 1023.0);
  float mq8_resistencia = 1000*((5-mq8_voltaje)/mq8_voltaje);
  double hidrogeno = 1803*pow(mq8_resistencia/5463, -0.66);
  String mq8_umbral = "false";

  if(digitalRead(7) == 0){
    mq8_umbral = "true";
  }

  // MQ9 Blanco
  // -- TODO --

  // JSON
  String debugSerial = "";
  String jsonSerial = "{";

    // DHT22, AM2302
  if (isnan(temperatura) || isnan(humedad)) {

    jsonSerial += "\"humedad\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    jsonSerial += "\"temperatura\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";   
    jsonSerial += "}";

    debugSerial += "DHT22 : Error\n";

  } else {
  
    debugSerial += temperatura;
    debugSerial += " C ";
    debugSerial += humedad ;
    debugSerial += "%  ";
    debugSerial += "\n";
    
    lcd.setCursor(0,1);
    lcd.print(debugSerial);
    
    debugSerial = "DHT22 : " + debugSerial;

    jsonSerial += "\"humedad\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":";
    jsonSerial += humedad;
    jsonSerial += ",\"sensor\": \"AM2302\",";
    jsonSerial += "\"unidad\": \"%\"";  
    jsonSerial += "},";
    
    jsonSerial += "\"temperatura\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":";
    jsonSerial += temperatura;
    jsonSerial += ",\"sensor\": \"DHT22\",";
    jsonSerial += "\"unidad\": \"°C\"";    
    jsonSerial += "}";    
      
  }
  
  // MQ-135
  if (isnan(dioxidoDeCarbono) || isnan(oxidosDeNitrogeno) || isnan(amoniaco)) {

    jsonSerial += "\"dioxidoDeCarbono\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

    jsonSerial += "\"oxidosDeNitrogeno\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

    jsonSerial += "\"amoniaco\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

    debugSerial += "MQ-135: Error\n";
    
  } else {

    debugSerial += "MQ-135 :";
    debugSerial += " amoniaco: ";
    debugSerial += amoniaco;
    debugSerial += " dioxidoDeCarbono: "; 
    debugSerial += dioxidoDeCarbono;
    debugSerial += " oxidosDeNitrogeno: ";
    debugSerial += oxidosDeNitrogeno;
    debugSerial += "\n";

    jsonSerial += "\"amoniaco\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += amoniaco;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Amoníaco\",";      
    jsonSerial += "\"formulaQuimica\": [\"NH3\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},";
    
    jsonSerial += "\"dioxidoDeCarbono\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += dioxidoDeCarbono;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Dióxido de carbono\",";      
    jsonSerial += "\"formulaQuimica\": [\"CO2\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},";

    jsonSerial += "\"oxidosDeNitrogeno\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += oxidosDeNitrogeno;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Óxidos de nitrógeno (Óxido nitroso, Óxido nítrico, Anhídrido nitroso, Tetraóxido de nitrógeno, Peróxido nítrico, Anhídrido nítrico)\",";      
    jsonSerial += "\"formulaQuimica\": [\"NOx\", \"N2O\", \"NO\", \"N2O3\", \"N2O4\", \"NO2\", \"N2O5\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},"; 
  }

  // MQ-2
  if (isnan(glp)) {
    
    jsonSerial += "\"glp\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-2  : Error\n";
    
  } else {

    debugSerial += "MQ-2: ";
    debugSerial += "glp: ";
    debugSerial += glp;
    debugSerial += "\n";

    jsonSerial += "\"glp\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += glp;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Gas licuado del petróleo (Propano, Butano, ambos)\",";      
    jsonSerial += "\"formulaQuimica\": [\"C3H8\", \"C4H10\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq2_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq2_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq2_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq2_adc;
    jsonSerial += ",\"sensor\": \"MQ-2\"";
    jsonSerial += "},";  

  }
  
  //MQ-3
  if (isnan(alcohol)) {
  
    jsonSerial += "\"alcohol\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-3  : Error\n";
    
  } else {

    debugSerial += "MQ-3: ";
    debugSerial += "alcohol: ";
    debugSerial += alcohol;
    debugSerial += "\n";
    
    jsonSerial += "\"alcohol\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += alcohol;
    jsonSerial += ",\"unidad\": \"mg/L\",";
    jsonSerial += "\"descripcion\": \"Alcohol (Benceno, Propano, Etanol, Metanol)\",";      
    jsonSerial += "\"formulaQuimica\": [\"C6H6\", \"C3H8\", \"C2H6O\", \"CH3OH\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq3_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq3_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq3_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq3_adc;
    jsonSerial += ",\"sensor\": \"MQ-3\"";
    jsonSerial += "},";     

  }

  // MQ-4
  if (isnan(metano)) {

    jsonSerial += "\"metano\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-4  : Error\n";

  } else {

    debugSerial += "MQ-4: ";
    debugSerial += "metano: ";
    debugSerial += metano;
    debugSerial += "\n";

    jsonSerial += "\"metano\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += metano;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Gas natural, Metano\",";      
    jsonSerial += "\"formulaQuimica\": [\"CH4\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq4_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq4_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq4_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq4_adc;
    jsonSerial += ",\"sensor\": \"MQ-4\"";
    jsonSerial += "},"; 

  }

  // MQ-6
  if (isnan(propano)) {

    jsonSerial += "\"propano\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-6  : Error\n";

  } else {

    debugSerial += "MQ-6: ";
    debugSerial += "propano: ";
    debugSerial += propano;
    debugSerial += "\n";

    jsonSerial += "\"propano\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += propano;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Propano\",";      
    jsonSerial += "\"formulaQuimica\": [\"C3H8\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq6_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq6_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq6_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq6_adc;
    jsonSerial += ",\"sensor\": \"MQ-6\"";
    jsonSerial += "},";

  }
  
  // MQ-7
  if (isnan(monoxidoDeCarbono)) {

    jsonSerial += "\"monoxidoDeCarbono\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-7  : Error\n";

  } else {

    debugSerial += "MQ-7: ";
    debugSerial += "monoxidoDeCarbono: ";
    debugSerial += monoxidoDeCarbono;
    debugSerial += "\n";

    jsonSerial += "\"monoxidoDeCarbono\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += monoxidoDeCarbono;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Monóxido de Carbono\",";      
    jsonSerial += "\"formulaQuimica\": [\"CO\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq7_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq7_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq7_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq7_adc;
    jsonSerial += ",\"sensor\": \"MQ-7\"";
    jsonSerial += "},";

  }

  // MQ-8
  if (isnan(hidrogeno)) {

    jsonSerial += "\"hidrogeno\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    debugSerial += "MQ-8  : Error\n";
    
  } else {

    debugSerial += "MQ-8: ";
    debugSerial += "hidrogeno: ";
    debugSerial += hidrogeno;
    debugSerial += "\n";

    jsonSerial += "\"hidrogeno\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += hidrogeno;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Hidrógeno\",";      
    jsonSerial += "\"formulaQuimica\": [\"H2\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq8_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq8_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq8_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq8_adc;
    jsonSerial += ",\"sensor\": \"MQ-8\"";
    jsonSerial += "},";  

  }

  jsonSerial += "}";

  // Impresión
  if(DEBUG==true) { 
    Serial.println(debugSerial);
  } else {
    Serial.println(jsonSerial);
  }
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
