#include "ShiftRegister595.h"
 
byte latchPin = A1;  //Pin connected to ST_CP of 74HC595
byte clockPin = A0; //Pin connected to SH_CP of 74HC595
byte dataPin = A2;  //Pin connected to DS    of 74HC595
 
ShiftRegister595 shiftRegister595 = ShiftRegister595( latchPin , clockPin , dataPin );
 
 
void setup() {
}
 
void loop() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    shiftRegister595.write(j);
    delay(500);
  }
}
