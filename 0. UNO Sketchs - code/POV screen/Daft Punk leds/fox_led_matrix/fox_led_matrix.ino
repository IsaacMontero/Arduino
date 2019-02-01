


int ENABLE=4;
int CLEAR=3;

#define LATCH A1  //Pin conectado a ST_CP of 74HC595 (Amarillo)
#define CLOCK A0  //Pin conectado a SH_CP of 74HC595 (Verde)
#define DATA A2   //Pin connected to DS of 74HC595  (Azul)

int smily[][8]={{60,66,129,165,129,165,90,60},
                {3,7,14,92,120,112,120,128},
                {122,141,109,121,159,166,161,94},
                {14,144,144,158,121,9,9,112},
                {207,255,194,218,91,67,255,243},
                {126,243,191,192,253,253,207,126}

};

int anim1[][8]={{170,1,128,1,128,1,128,85},
                {85,128,1,128,1,128,1,170}


};


int anim2[][8]={{0,0,0,24,24,0,0,0},
                {0,0,60,36,36,60,0,0},
                {0,126,66,66,66,66,126,0},
                {255,129,129,129,129,129,129,255}

};



int zero[] ={0,62,34,34,34,34,34,62};
int one[] ={0,8,24,40,8,8,8,62};
int two[] ={0,62,2,2,62,32,32,62};
int three[] ={0,62,2,2,62,2,2,62};
int four[] ={0,4,12,20,36,126,4,4};
int five[] ={0,62,32,32,62,2,2,62};
int six[] ={0,62,32,32,62,34,34,62};
int seven[] ={0,62,2,4,8,16,32,32};
int eight[] ={0,62,34,34,62,34,34,62};
int nine[] ={0,62,34,34,62,2,2,62};


char oussama[][8]={{60,66,129,129,129,129,66,60},      //O
                  {129,129,129,129,129,129,66,60}, //U
                  {63,64,128,128,126,1,1,254},   //S
                  {63,64,128,128,126,1,1,254},   //S
                  {24,36,66,129,255,129,129,129},  //A
                  {129,195,165,153,129,129,129,129},   //M
                  {24,36,66,129,255,129,129,129}   //A
                
              
            
};


void setup(){
  
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(CLEAR, OUTPUT);

  
  digitalWrite(LATCH,LOW);
  digitalWrite(CLOCK,LOW);
  digitalWrite(DATA,LOW);
  
  digitalWrite(ENABLE,LOW);
  digitalWrite(CLEAR,HIGH);
  
}



void Matrixseq(int moveSpeed){
  
  
   int r=1;
   int c=1;
  
  
   for(int i=0;i<8;i++){
    
      r=1;
     for(int j=0;j<8;j++){
     
       digitalWrite(LATCH,LOW);
       //delay(1);

                
      shiftOut(DATA, CLOCK, MSBFIRST, ~r); 
      shiftOut(DATA, CLOCK, LSBFIRST, c); 
  
      //delay(1);
      digitalWrite(LATCH,HIGH);
     
      r = r << 1;
     
      delay(moveSpeed);
     }

     c = c << 1; 
    
  }
  
  
}


void matrixDisplay(int data[],int duration){
  
  int r;
  
  for(int x=0;x<duration;x++){
    
  r=1;
  
  for(int i=0;i<8;i++){
    

       digitalWrite(LATCH,LOW);
       //delay(1);

                
      shiftOut(DATA, CLOCK, MSBFIRST, ~r); 
      shiftOut(DATA, CLOCK, LSBFIRST, data[i]); 
  
      //delay(1);
      digitalWrite(LATCH,HIGH);
      
      
      delay(2);

      r = r << 1;
    
  }
  
  }
  
}


void matrixDisplayV(int data[],int duration){
  
  int r;
  
  for(int x=0;x<duration;x++){
    
  r=1;
  
  for(int i=0;i<8;i++){
    

       digitalWrite(LATCH,LOW);
       //delay(1);

                
      shiftOut(DATA, CLOCK, MSBFIRST, ~data[i]); 
      shiftOut(DATA, CLOCK, MSBFIRST, r); 
  
      //delay(1);
      digitalWrite(LATCH,HIGH);
      
      
      delay(2);

      r = r << 1;
    
  }
  
  }
  
}


void matrixVscroll(int data[],int duration){
  
  int r;
  
    
  char dd[8]={};
  
  memcpy(dd,data,8);
  
  for(int x=0;x<duration;x++){
    
  r=1;
  
  for(int i=0;i<8;i++){
    

       digitalWrite(LATCH,LOW);
       //delay(1);

                
      shiftOut(DATA, CLOCK, MSBFIRST, ~data[i]); 
      shiftOut(DATA, CLOCK, MSBFIRST, r); 
  
      //delay(1);
      digitalWrite(LATCH,HIGH);
      
      
      delay(2);

      r = r << 1;
    
  }
  
  }
  
}

void matrixScroll(char data[],int duration){
  
  int r;
  int counter=7;
  
  char dd[8]={};
  
  memcpy(dd,data,8);
  
 for(int s=0;s<8;s++){
  
  for(int x=0;x<duration;x++){
    
  r=1;
  
  for(int l=0;l<counter;l++){
    
    digitalWrite(LATCH,LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, ~r); 
    shiftOut(DATA, CLOCK, LSBFIRST, 0);
    
    digitalWrite(LATCH,HIGH);
    
    delay(2);
    
    r = r << 1;
    
  }
  
  for(int i=0;i<8-counter;i++){
    
      digitalWrite(LATCH,LOW);
       
      shiftOut(DATA, CLOCK, MSBFIRST, ~r); 
      shiftOut(DATA, CLOCK, LSBFIRST, dd[i]);
      

      digitalWrite(LATCH,HIGH);
      
      
      delay(2);

      r = r << 1;
    
  }
  
   
   
  
  }
  counter --;
  
  //counter=8;
  //delay(2);
  /*for(int h=0;h<8;h++){
    dd[h]=dd[h] << 1;
  }*/
  
}
  
}



void loop(){


  /*matrixScroll(ch,5);
  matrixScroll(ch2,5);*/
  
 for(int i=0;i<10;i++){
  matrixDisplay(anim1[0],10);
  matrixDisplay(anim1[1],10);
 }
  
 for(int i=0;i<10;i++){
  matrixDisplay(anim2[0],10);
  matrixDisplay(anim2[1],10);
  matrixDisplay(anim2[2],10);
  matrixDisplay(anim2[3],10);
  
 }
  
  
  
  Matrixseq(50);
  Matrixseq(25);
  Matrixseq(10);
  Matrixseq(5);
  Matrixseq(5);
  Matrixseq(5);
  Matrixseq(0);

  
  matrixScroll(oussama[0],5);
  matrixScroll(oussama[1],5);
  matrixScroll(oussama[2],5);
  matrixScroll(oussama[3],5);
  matrixScroll(oussama[4],5);
  matrixScroll(oussama[5],5);
  matrixScroll(oussama[6],5);
  
    
  

  

  matrixDisplay(smily[0],100);
  matrixDisplay(smily[1],100);
  matrixDisplay(smily[2],100);
  matrixDisplay(smily[3],100);
  matrixDisplay(smily[4],100);
  matrixDisplay(smily[5],100);

  matrixDisplay(zero,20);  
  matrixDisplay(one,20);
  matrixDisplay(two,20);
  matrixDisplay(three,20);
  matrixDisplay(four,20);
  matrixDisplay(five,20);
  matrixDisplay(six,20);
  matrixDisplay(seven,20);
  matrixDisplay(eight,20);
  matrixDisplay(nine,20);



}
