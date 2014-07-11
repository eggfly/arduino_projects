#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
double ax2, ay2, az2, r;
char accStr[32];
char fpsStr[32];
char uptimeStr[16];
unsigned long t = 0;
unsigned long lastRefreshClockTime = 0;

int led = 13;
int ledState = HIGH;

void setup() {
  accelgyro.initialize();
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  Serial.println("Bluetooth init..");
}


void loop() {
  Serial.println("hello");
  delay(200);
  // led
  digitalWrite(led, ledState);   // turn the LED on (HIGH is the voltage level)
  ledState = !ledState;

// accelgyro
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax2  =ax/16384.0;
  ay2 = ay/16384.0;
  az2 = az/16384.0;
  r = sqrt(ax2*ax2 + ay2*ay2 + az2*az2);
  dtostrf(r,1,4, accStr);
  // fps and uptime
  unsigned long ms = millis();
  dtostrf(ms/1000.0,1,2,uptimeStr);
  sprintf(uptimeStr, "%ss", uptimeStr);
  // itoa(ms, uptimeStr, 10);
  unsigned long delta = ms - t;
  t = ms;
  double fps = 1000.0 / delta;
  dtostrf(fps, 1, 1, fpsStr);
  sprintf(fpsStr, "%s fps", fpsStr);

  // clock
  if (ms - lastRefreshClockTime > 200){
    lastRefreshClockTime = ms;
    /* refresh当前时间 */
    //query_time();
  }
    Serial.print(fpsStr);
    Serial.print(", ");
    Serial.print(uptimeStr);
    Serial.print(", ");
    Serial.println(accStr);
}




