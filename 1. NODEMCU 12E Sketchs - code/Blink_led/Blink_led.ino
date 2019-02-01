#define LED_BUILTIN 2

void setup() {

pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
delay(1000);
Serial.print("Ready – ");

}

void loop() {
Serial.println("ON");
digitalWrite(LED_BUILTIN,LOW);
delay(1000);
Serial.println("OFF");
digitalWrite(LED_BUILTIN,HIGH);
delay(1000);
}
