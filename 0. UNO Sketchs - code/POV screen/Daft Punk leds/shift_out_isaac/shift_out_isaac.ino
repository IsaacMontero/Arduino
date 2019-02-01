/*
  ShiftRegister17x7.h - Library for easy control of the 74HC595B shift register.
  Created by Isaac Montero, Jan 2017.
  Additional information are available on http://shiftregister.simsso.de/
*/

#include <ShiftRegister17x7.h>
#include <Ascii_Control.h>

//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin 9
#define clockPin 8
#define dataPin 10

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister17x7 sr(3, dataPin, clockPin, latchPin);
Ascii_Control ascii;

void setup() {
  Serial.begin(9600);
}

void loop() {

  /*
       17 x 7 Matrix 3 shift controllerbyte ** pinValues 74HC595
  */

  byte pinValues1[7][3] = { { B11111101 , B01010101, B11000000 },
                            { B11111011 , B11111111, B11100000 },
                            { B11110111 , B01010101, B11110000 },
                            { B11101111 , B11111111, B11111000 },
                            { B11011111 , B01010101, B11111100 },
                            { B10111111 , B11111111, B11111110 },
                            { B01111111 , B01010101, B11111111 }
                          };
  sr.setAll(pinValues1);
  sr.displayAll();
}
