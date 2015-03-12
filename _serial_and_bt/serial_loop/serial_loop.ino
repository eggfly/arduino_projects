char incomingByte;  // incoming data
int  LED = 13;      // LED pin

void setup() {
  Serial.begin(9600); // initialization
  pinMode(LED, OUTPUT);
  Serial.println("Press 1 to LED ON or 0 to LED OFF...");
}

void loop() {
       Serial.println("LED ON. Press 0 to LED OFF!");
       delay(1000);
}
