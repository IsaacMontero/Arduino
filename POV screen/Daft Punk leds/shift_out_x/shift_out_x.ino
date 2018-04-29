//**************************************************************//
//  Name    : shiftFourRegisters                                
//  Author  : Juan Hernandez
//  Date    : 02 Jan 2011    
//  Modified:                                  
//  Version : 1.0                                            
//  Notes   : Code for using four 74HC595 Shift Registers           //
//          : with shiftOutX class                          
//****************************************************************
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
//this are the input parameters to the class constructor

//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin A1
#define clockPin A0
#define dataPin A2

//shiftOutX(_latchPin, _dataPin, _clockPin, _bitOrder, _NofRegisters);
shiftOutX regOne(latchPin, clockPin, dataPin, MSBFIRST, 23);

void setup() {
 
}
 
void loop() {  
  regOne.pinOff(shPin28); //turn on pin Q3 of shift
  //register number 4 since they are
  //daisy chained it is pin number 28 in this case it is
  //named shPin28 "shift registers pin 28"
  delay(200);
  regOne.pinOn(shPin28);
  delay(200);  
  regOne.pinOff(shPin7);
  delay(200);
  regOne.pinOn(shPin7);  //turn on pin Q6 of shift register
  //number 1
  delay(200);
  regOne.pinOff(shPin13); //turn off pin Q4 of shift
  //register number 2
  delay(200);
  regOne.pinOn(shPin13);
  delay(200);
  regOne.pinOff(shPin20);
  delay(200);
  regOne.pinOn(shPin20);
  delay(200);
 
  if (regOne.pinState(shPin20) == true) //check if shPin20
  //is on, you can use ON, OFF, or true or false
  {
    regOne.pinOn(shPin32); //turn on pin Q7 of shift
  //register number 4
    delay(1000);
    regOne.pinOff(shPin32);
  }
  delay(1000);
  regOne.allOn(); //turn all the pins on
  delay(1000);
  regOne.allOff(); //turn all the pins off
  delay(1000);
 
}
