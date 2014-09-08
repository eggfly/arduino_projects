#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 2  //for Leonardo：10, bluetooth tx
#define TxD 3  //for Leonardo：11, bluetooth rx

char incomingByte;  // incoming data
int  LED = 13;      // LED pin
SoftwareSerial blueToothSerial(RxD,TxD);

void setup() {
  Serial.begin(9600); // initialization
  pinMode(LED, OUTPUT);
  Serial.println("Hello remote control!");
  blueToothSerial.begin(9600);
}

void loop() {
  if (blueToothSerial.available() > 0) {  // if the data came
    incomingByte = blueToothSerial.read(); // read byte
    if(incomingByte == '0') {
      digitalWrite(LED, LOW);  // if 1, switch LED Off
      blueToothSerial.println("LED OFF. Press 1 to LED ON!");  // print message
    }
    if(incomingByte == '1') {
      digitalWrite(LED, HIGH); // if 0, switch LED on
      blueToothSerial.println("LED ON. Press 0 to LED OFF!");
    }
  }
}

