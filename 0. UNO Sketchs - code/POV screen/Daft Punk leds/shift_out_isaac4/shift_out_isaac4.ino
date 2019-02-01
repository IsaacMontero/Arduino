/*
  ShiftRegister17x7.h - Library for easy control of the 74HC595B shift register.
  Created by Isaac Montero, Jan 2017.
  Additional information are available on http://shiftregister.simsso.de/
*/

#include <ShiftRegister17x7.h>
//#include <Ascii_Control.h>

#define latchPin 9
#define clockPin 8
#define dataPin 10

// Initialize objects
ShiftRegister17x7 sr(3, dataPin, clockPin, latchPin);
//Ascii_Control ascii;

// List of supported characters and index into corresponding character definitions array
const byte charSet[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&'()*+-,.~:;<>?@[]/\\=_";
// Character definitions (8 bytes per character)
const byte charDef[] = {
  0,0,0,0,0,0,0,0,                // Space symbol (must be the first character in this array)
  // Upper case letters:
  24,60,102,126,102,102,102,0,    // A
  124,102,102,124,102,102,124,0,  // B
  60,102,96,96,96,102,60,0,       // C
  120,108,102,102,102,108,120,0,  // D
  126,96,96,120,96,96,126,0,      // E
  126,96,96,120,96,96,96,0,       // F
  60,102,96,110,102,102,60,0,     // G
  102,102,102,126,102,102,102,0,  // H
  60,24,24,24,24,24,60,0,         // I
  30,12,12,12,12,108,56,0,        // J
  102,108,120,112,120,108,102,0,  // K
  96,96,96,96,96,96,126,0,        // L
  99,119,127,107,99,99,99,0,      // M
  102,118,126,126,110,102,102,0,  // N
  60,102,102,102,102,102,60,0,    // O
  124,102,102,124,96,96,96,0,     // P
  60,102,102,102,102,60,14,0,     // Q
  124,102,102,124,120,108,102,0,  // R
  60,102,96,60,6,102,60,0,        // S
  126,24,24,24,24,24,24,0,        // T
  102,102,102,102,102,102,60,0,   // U
  102,102,102,102,102,60,24,0,    // V
  99,99,99,107,127,119,99,0,      // W
  102,102,60,24,60,102,102,0,     // X
  102,102,102,60,24,24,24,0,      // Y
  126,6,12,24,48,96,126,0,        // Z
  // Lower case letters:
  0,0,60,6,62,102,62,0,           // a
  0,96,96,124,102,102,124,0,      // b
  0,0,60,96,96,96,60,0,           // c
  0,6,6,62,102,102,62,0,          // d
  0,0,60,102,126,96,60,0,         // e
  0,14,24,62,24,24,24,0,          // f
  0,62,102,102,62,6,124,0,        // g
  0,96,96,124,102,102,102,0,      // h
  0,24,0,56,24,24,60,0,           // i
  6,0,6,6,6,6,60,0,               // j
  0,96,96,108,120,108,102,0,      // k
  0,56,24,24,24,24,60,0,          // l
  0,0,102,127,127,107,99,0,       // m
  0,0,124,102,102,102,102,0,      // n
  0,0,60,102,102,102,60,0,        // o
  0,124,102,102,124,96,96,0,      // p
  0,62,102,102,62,6,6,0,          // q
  0,0,124,102,96,96,96,0,         // r
  0,0,62,96,60,6,124,0,           // s
  0,24,126,24,24,24,14,0,         // t
  0,0,102,102,102,102,62,0,       // u
  0,0,102,102,102,60,24,0,        // v
  0,0,99,107,127,62,54,0,         // w
  0,0,102,60,24,60,102,0,         // x
  0,102,102,102,62,12,120,0,      // y
  0,0,126,12,24,48,126,0,         // z
  // Numbers
  60,102,110,118,102,102,60,0,    // 0
  24,24,56,24,24,24,126,0,        // 1
  60,102,6,12,48,96,126,0,        // 2
  60,102,6,28,6,102,60,0,         // 3
  6,14,30,102,127,6,6,0,          // 4
  126,96,124,6,6,102,60,0,        // 5
  60,102,96,124,102,102,60,0,     // 6
  126,102,12,24,24,24,24,0,       // 7
  60,102,102,60,102,102,60,0,     // 8
  60,102,102,62,6,102,60,0,       // 9
  // Characters and symbols
  24,24,24,24,0,0,24,0,           // !
  102,102,255,102,255,102,102,0,  // #
  24,62,96,60,6,124,24,0,         // $
  98,102,12,24,48,102,70,0,       // %
  60,102,60,56,103,102,63,0,      // &
  6,12,24,0,0,0,0,0,              // '
  12,24,48,48,48,24,12,0,         // (
  48,24,12,12,12,24,48,0,         // )
  0,102,60,255,60,102,0,0,        // *
  0,24,24,126,24,24,0,0,          // +
  0,0,0,126,0,0,0,0,              // -
  0,0,0,0,0,24,24,48,             // ,
  0,0,0,0,0,24,24,0,              // .
  60,66,165,129,165,153,66,60,    // ":)" (~) character
  0,24,0,0,24,0,0,0,              // :
  0,24,0,0,24,24,48,0,            // ;
  14,24,48,96,48,24,14,0,         // <
  112,24,12,6,12,24,112,0,        // >
  60,102,6,12,24,0,24,0,          // ?
  60,102,110,110,96,98,60,0,      // @
  60,48,48,48,48,48,60,0,         // [
  60,12,12,12,12,12,60,0,         // ]
  0,3,6,12,24,48,96,0,            // /
  0,96,48,24,12,6,3,0,            // \
  0,0,126,0,126,0,0,0,            // =
  0,0,0,0,0,0,255,0,              // _
};

//Initialize global vars.
const char charMsg[] = "3 Shift Register controller LED Matrix 17x7. Isaac Montero";

// Number of milliseconds to pause after message (0 = no pause):
unsigned const msgPauseTime = 2000;
// Controls the message scroll speed in ms (lower = faster):
const int scrollSpeed = 75;
unsigned long thisMs = 0;         // Elapsed time in ms that Arduino has been running
unsigned long lastMs;             // Interval since the message was last scrolled one column
unsigned long pauseStart;         // Elapsed time in ms since end-of-message pause was started
int msgIdx = 0;                   // Keeps track of the message character current being scrolled
byte charBuffer[16];              // Scroll "window" consists of portions of current and next character
byte charBuffer1[8];              // Second Shift Register
byte charBuffer2[8];              // Third Shift Register
int bufferIdx = 0;                // Keeps track of scrolling (after 8 columns, fetch next character)
boolean pauseDisplay = false;     // Determines when scrolling should be paused


void setup() {
  Serial.begin(9600);
}

void loop() {
  thisMs = millis();              // Get current time
  if (thisMs - lastMs > scrollSpeed) {  // Time to scroll yet?
    lastMs = thisMs;              // Yes, so save current time value
    if (pauseDisplay == true) {   // Don't scroll if we're at the end of the message
      if (thisMs - pauseStart > msgPauseTime)  // Has the pause time elapsed?
      initialize();               // Yes, so get ready to display the banner message again
    }
    else
      scrollDisplay();            // We're not at the end of the message, so scroll away!
  }
   //reset the matrix
   byte pinValues[7][3]  =  { { B11111100 , 0, 0 },
                              { B11111010 , 0, 0 },
                              { B11110110 , 0, 0 },
                              { B11101110 , 0, 0 },
                              { B11011110 , 0, 0 },
                              { B10111110 , 0, 0 },
                              { B01111110 , 0, 0 }
                            };
  for (int y = 0; y < 8; y++) {
    bool bufferByte2[8] = {};
    for (int x = 0; x < 8; x++) {
        bufferByte2[x] =  (charBuffer2[y] >> (x) & 1);
    }
    bool bufferByte1[8] = {};
    for (int x = 0; x < 8; x++) {
        bufferByte1[x] =  (charBuffer1[y] >> (x) & 1);
    }
    bool bufferByte[8] = {};
    for (int x = 0; x < 8; x++) {
        bufferByte[x] =  (charBuffer[y] >> (x) & 1);
    }
    if(y<7){ //we just have got 7 rows
      pinValues[y][0] = pinValues[y][0] | (sr.SetByte(bufferByte2) & B00000001);
      pinValues[y][1] = sr.SetByte(bufferByte1);
      pinValues[y][2] = sr.SetByte(bufferByte);
    }
  }
  sr.setAll(pinValues);
  sr.displayAll();
}


void initialize() {
  // Prepare to start displaying banner message
    for (int i = 0; i < 8; i++) {
      charBuffer[i] = 0;         // Clear scrolling buffer prior to displaying the message
      charBuffer1[i] = 0;
      charBuffer2[i] = 0;
    }
    msgIdx = 0;                  // Reset pointer to first character in the message
    fetchChar();                 // Read first character in message and prepare to scroll it
    pauseDisplay = false;        // No need to pause, since we're starting over again
}

void fetchChar() {
  int foundVal = 0;
  // Check to see whether we've reached the end of the null-terminated message character string
  if (charMsg[msgIdx] == 0) {
    msgIdx = 0;
    pauseDisplay = true;
    pauseStart = thisMs;
  }
  // For each character in the message, make sure there is a matching character definition
  for (int i = 0; i < 89; i++) // TODO 89+
    if (charMsg[msgIdx] == charSet[i]) {
      foundVal = i;
    }
  msgIdx++;
  // Load 3 chararctes for the first time to fill the buffer;
  // Load the scroll buffer with the newly-found character (or blank, if none was found)
  for (int i = 0; i < 8; i++) {
    charBuffer[i + 8] = charDef[foundVal * 8 + i];
  }
}

void scrollDisplay() {
  // Scroll the current message character one column to the left
  for (int x = 0; x < 8; x++) {
    charBuffer2[x] = charBuffer2[x] << 1;
    if (charBuffer1[x] & 128) {
      charBuffer2[x] = charBuffer2[x] | 1;
    }
  }
  for (int x = 0; x < 8; x++) {
    charBuffer1[x] = charBuffer1[x] << 1;
    if (charBuffer[x] & 128) {
      charBuffer1[x] = charBuffer1[x] | 1;
    }
  }
  for (int x = 0; x < 8; x++) {
    charBuffer[x] = charBuffer[x] << 1;
    if (charBuffer[x + 8] & 128) {
      charBuffer[x] = charBuffer[x] | 1;
    }
    charBuffer[x + 8] = charBuffer[x + 8] << 1;
  }
  // After 8 columns have been scrolled, fetch the next character
  bufferIdx++;
  if (bufferIdx > 7) {
    bufferIdx = 0;
    fetchChar();
  }
}
