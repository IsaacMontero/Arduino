// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  }

int ledv = 13;
int ledr = 8;

void loop() {
  bool val = digitalRead(ledv);
  digitalWrite(ledv, !val); 
  digitalWrite(ledr, val);
  delay(200);
}

