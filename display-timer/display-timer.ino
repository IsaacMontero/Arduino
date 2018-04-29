#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() 
   {
       lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas
       lcd.print("  Test Timer :");  // Aqi va el mensaje
       pinMode(13, OUTPUT);
       digitalWrite(13, HIGH);
   }

void loop()
   {
       lcd.setCursor(6, 1);    // Ponte en la line 1, posicion 6
       String s = reloj() ;
       lcd.print(s) ;
   }
String reloj()
   {
       int n = millis() / 1000 ;       // Lo pasamos a segundos
       int segundos = n % 60  ;
       int minutos =  n / 60  ;

       String S = String(minutos) + ":" + String(segundos);
       return (S);
   }
