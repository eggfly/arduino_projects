const int led = 13;
void setup() {
  Serial.begin(9600);
  Serial.println("arduino uno started!");
  pinMode(led, OUTPUT); 
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    char c = Serial.read();
    Serial.write(c);
    if (c == '1') {
      digitalWrite(led, HIGH);
    } 
    else if(c=='0'){
      digitalWrite(led, LOW);
    }
  }
}









