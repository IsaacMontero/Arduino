int analogPin = A1;
        /* el pin analógico que usaremos en Arduino */

int myNTC= 0;
        /* variable temporal para guardar los valores del termómetro */

void setup(){
        Serial.begin(9600);
        /* configurando la comunicación y la velocidad */
}

void loop(){
        myNTC = analogRead(analogPin);
        /* lee el valor del NTC y lo almacena */
        Serial.println(myNTC);
        /* muestra el valor almacenado en myNTC */
        delay(200);
}
