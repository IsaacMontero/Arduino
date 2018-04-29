/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>

//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin A1
#define clockPin A0
#define dataPin A2

// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (3, dataPin, clockPin, latchPin); 
 
void setup() { 
    Serial.begin(9600);
}

void loop() {

  uint8_t pinValues[] = { B11111110 , B00000000, B00000000 } ;
  sr.setAll(pinValues); 
  //delay(500);
  
  
/*
  for (int i = 0; i < 100; i ++ ) {
    Serial.println(i);
    sr.set(i, HIGH); // set single pin HIGH
    delay(500); 
    if(i == 6){
      sr.setAllLow();
      i = -1;
    }
  }
  */
  /*
  // set all pins at once
  uint8_t pinValues[] = { B10101010 }; 
  sr.setAll(pinValues); 
  delay(1000);
  
  // read pin (zero based)
  uint8_t stateOfPin5 = sr.get(5);
  */
}
