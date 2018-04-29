#include "IRLremote.h"
const int interruptIR = 0;

uint8_t IRProtocol = 0;  // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

void setup() 
   {    Serial.begin(115200);          // Fijate en la velocidad
        for (int i = 10 ; i<=13 ; i++)
        pinMode(i, OUTPUT);

        IRLbegin<IR_ALL>(interruptIR);
   }
void loop()
   {    uint8_t oldSREG = SREG;  // Parar las interrupciones
        cli();
        if (IRProtocol)
          {  
              switch (IRCommand) // Aqui tenemos la clausula switch con sus case:
                  { case 0x02FD:
                        Serial.println("Arriba");
                        digitalWrite(13, HIGH);
                        break;
                    case 0x827D:
                        Serial.println("Abajo");
                        digitalWrite(12, HIGH);
                        break;
                    case 0xE01F:
                         Serial.println("Izquierda");
                         digitalWrite(11, HIGH);
                         break;
                    case 0x609F:
                         Serial.println("Derecha");
                         digitalWrite(10, HIGH);
                         break;
                    case 0x22DD:
                         Serial.println("OK");
                         for (int k =0 ; k <=13 ; k++) 
                              digitalWrite(k, LOW);
                         break;
                  }
              IRProtocol = 0;
          }
       SREG = oldSREG; 
    }
void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
   {
        IRProtocol = protocol;  // Recogemos los valores
        IRAddress = address;
        IRCommand = command;
   }
