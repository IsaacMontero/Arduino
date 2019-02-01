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

void setup()
{
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Hello, World");    // change this text to whatever you like. keep it clean.
  lcd.setCursor(0,1);           // set cursor to column 0, row 1
  lcd.print("Isaac Montero");
  
  // if you have a 4 row LCD, uncomment these lines to write to the bottom rows
  // and change the lcd.begin() statement above.
  //lcd.setCursor(0,2);         // set cursor to column 0, row 2
  //lcd.print("Row 3");
  //lcd.setCursor(0,3);         // set cursor to column 0, row 3
  //lcd.print("Row 4");
}

void loop()
{
}
