void setup()
   {
       for (int i =9 ; i<12 ; i++)
            pinMode(i, OUTPUT);
   }
void Color(int R, int G, int B)
    {     
        analogWrite(9 , G) ;   // Red    - Rojo
        analogWrite(10, B) ;   // Green - Verde
        analogWrite(11, R) ;   // Blue - Azul
    }
void loop()
   {    Color(255 ,0 ,0) ;
   }
