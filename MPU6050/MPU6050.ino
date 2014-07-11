#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
double ax2, ay2, az2, r;

bool blinkState = false;

void setup() {

  Wire.begin();
  Serial.begin(9600);

  accelgyro.initialize();
}
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax2  =ax/16384.0;
  ay2 = ay/16384.0;
  az2 = az/16384.0;
  r = sqrt(ax2*ax2 + ay2*ay2 + az2*az2);
  //Serial.print(",");
  //Serial.print(gx/131.0); 
  //Serial.print("\t");
  //Serial.print(gy/131.0); 
  //Serial.print("\t");
  //Serial.println(gz/131.0);
  Serial.println(r);
  blinkState = !blinkState;

}


