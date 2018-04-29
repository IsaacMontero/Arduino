// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(9, OUTPUT);
  }

void loop() {
 
  analogWrite(9, 0);

  int i = 0;
  bool sw = 0;
  while(i<=255){
      if(sw==0){
        analogWrite(9, i);
      }else{
        analogWrite(9, 100 - i);
      }
      if(i==255){
        sw=!sw;
        i=0;
      }
      i++;
      delay(10);
    }
      
    
}

