 void setup()
{ Serial.begin(115200); }

void loop ()
{ 
    char c = ' ' ;
    String mensaje ="" ;
    if (Serial.available()) //Comprobamos si hay algo esperando
         {
            while( c != '\n') //Si lo hay, lo leemos hasta el intro
                { 
                  mensaje = mensaje + c ; // Añadimos lo leído al mensaje
                  c = Serial.read(); //Leer 1 carácter
                  delay(25);
                }
            Serial.println( mensaje); //Al salir imprimir el mensaje
            mensaje = "" ; //Bórralo para la próxima vez
         }
}
