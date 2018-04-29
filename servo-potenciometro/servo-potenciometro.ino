#include <Servo.h>          // Incluir la librería Servo
Servo servo1;               // Crear un objeto tipo Servo llamado servo1
int angulo = 0 ;
void setup()
    {
       servo1.attach(9) ;  // Conectar servo1 al pin 9
       Serial.begin(9600);
    }

void loop()
    {
       angulo  = map( analogRead(A0), 0, 700, 11, 171);
       Serial.println(angulo);
       Serial.println(analogRead(A0));
       servo1.write(angulo);
       delay(250);
    }
