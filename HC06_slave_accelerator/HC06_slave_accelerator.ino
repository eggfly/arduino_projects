#include <SoftwareSerial.h>   //Software Serial Port
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define RxD 2  //for Leonardo：10, bluetooth tx
#define TxD 3  //for Leonardo：11, bluetooth rx

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define PARAMS 6
#define STR_LENGTH (PARAMS*6+PARAMS-1)
char accStr[STR_LENGTH];

char incomingByte;  // incoming data
int LED = 13;      // LED pin
byte led_digital = 0;

SoftwareSerial blueToothSerial(RxD,TxD);

void setup() {
  accelgyro.initialize();
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
      //      blueToothSerial.println("LED OFF. Press 1 to LED ON!");  // print message
    }
    if(incomingByte == '1') {
      digitalWrite(LED, HIGH); // if 0, switch LED on
      //      blueToothSerial.println("LED ON. Press 0 to LED OFF!");
    }
  }
  // toggle led
  digitalWrite(LED, led_digital);
  led_digital = !led_digital;
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  sprintf(accStr, "%d,%d,%d,%d,%d,%d", ax, ay, az, gx, gy, gz);
  blueToothSerial.println(accStr);
  delay(100);
}



