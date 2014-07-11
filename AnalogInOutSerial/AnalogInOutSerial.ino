const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}
int i = 0;
void loop() {
  i++;
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
//  Serial.print(i);
//  Serial.print(',');
  Serial.println(sensorValue);
  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(20);                     
}


