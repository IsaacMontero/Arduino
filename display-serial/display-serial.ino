#include <LiquidCrystal.h>

// Isaac Montero 23/01/2015
// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2

/*
 
 LCD Pin   Connect to
 1 (VSS)   GND Arduino pin*
 2 (VDD)   + 5v Arduino pin
 3 (contrast)  Resistor or potentiometer to GND Arduino pin*
 4 RS  Arduino pin 12
 5 R/W   Arduino pin 11
 6 Enable  Arduino pin 10
 7 No connection   
 8 No connection   
 9 No connection   
 10 No connection  
 11 (Data 4)   Arduino pin 5
 12 (Data 5)   Arduino pin 4
 13 (Data 6)   Arduino pin 3
 14 (Data 7)   Arduino pin 2
 15 Backlight +
 Resistor to Arduino pin 13**
 16 Backlight GND  GND Arduino pin*
 
*/

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int backLight = 13;    // pin 13 will control the backlight
String output = "";
 
void setup() {
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);  
  // initialize the serial communications:
  Serial.begin(115200);
}

void loop() {
  String line;
  char chara;
  
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    output = "";
    
      // read all the available characters
      // display each character to the LCD
       while(Serial.available()) {
          chara = Serial.read();
          output.concat(chara);
      }
      output.replace("\r\n", "");
      line = output.substring(0, 16);
      Serial.print(line);
      lcd.print(line);
      lcd.setCursor(0,1);
      line = output.substring(16, 32);
      Serial.println(line);
      lcd.print(line);
    }
    if(output==""){
      lcd.setCursor(0,0);
      lcd.print("Welcome Isaac");
      lcd.setCursor(0,1);
      lcd.print("Reading Serial:");
    }
}
