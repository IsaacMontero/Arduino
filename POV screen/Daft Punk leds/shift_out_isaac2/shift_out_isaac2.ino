/*
  ShiftRegister17x7.h - Library for easy control of the 74HC595B shift register.
  Created by Isaac Montero, Jan 2017.
  Additional information are available on http://shiftregister.simsso.de/
*/

#include <ShiftRegister17x7.h>
#include <Ascii_Control.h>
#include <TimerOne.h>

#define latchPin 9
#define clockPin 8
#define dataPin 10

// Initialize objects
ShiftRegister17x7 sr(3, dataPin, clockPin, latchPin);
Ascii_Control ascii;

//Initialize global vars.
const int led = 13;  // the pin with a LED
int ledState = LOW;    // El LED empieza apagado
int counter = 0;    // El LED empieza apagado
volatile unsigned long blinkCount = 0; // La definimos como volatile
byte pinValues[7][3];

void setup() {
  pinMode(led, OUTPUT);
  Timer1.initialize(500000);         // Dispara cada X ms
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  Serial.begin(9600);
}

void loop() {

  unsigned long N;  // Haremos copia del blinkCount
  digitalWrite(led, ledState);  // Asignamos el valor del status a la salida
  noInterrupts();               // Suspende las interrupciones
  N = blinkCount;
  interrupts();                 // Autoriza las interrupciones

  //Serial.print("Ciclos = ");
  //Serial.println(N);

  sr.displayAll();
}

void ISR_Blink() {
  ledState = !ledState ;
  if(ledState==0){
    if(counter>=9){
      counter=0;
    } else {
      counter++;
    }
  }
  if(ledState==1){
    byte pinValues1[7][3] = { { B11111101 , B11111111, B11111111 },
                              { B11111011 , B11111111, B11111111 },
                              { B11110111 , B11111111, B11111111 },
                              { B11101111 , B11111111, B11111111 },
                              { B11011111 , B11111111, B11111111 },
                              { B10111111 , B11111111, B11111111 },
                              { B01111111 , B11111111, B11111111 }
                            };
    sr.setAll(pinValues1);
  } else {
    byte pinValues2[7][3] = { { B11111100 , B00000000, B00000000 },
                              { B11111010 , B00000000, B00000000 },
                              { B11110110 , B00000000, B00000000 },
                              { B11101110 , B00000000, B00000000 },
                              { B11011110 , B00000000, B00000000 },
                              { B10111110 , B00000000, B00000000 },
                              { B01111110 , B00000000, B00000000 }
                            };
                            
    byte *c = ascii.LoadFont(counter + '0');
    for (int i = 0; i <7 ; i++)
    {
      byte C = c[i] ;
      for (int j =0; j < 8 ; j++)
      {
        bool b = sr.GetBit(C,j);
      }
      pinValues2[i][2] = C;
    }
    
    sr.setAll(pinValues2);

  }
  blinkCount++    ;     // Contador veces se enciende el LED
}
