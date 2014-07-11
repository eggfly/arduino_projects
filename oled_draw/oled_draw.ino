#include <U8glib.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
double ax2, ay2, az2, r;
char buffer[32];
int c = 0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
void draw() {
  u8g.setFont(u8g_font_unifont);
  //  u8g.drawStr( 0, 15, "Hello World!overflow line");
  //  u8g.drawStr( 10, 25, "Hello World!overflow line");
  u8g.drawStr(10,45, buffer);
}

void setup() {
  accelgyro.initialize();
}
void loop() {
  u8g.firstPage();  
  u8g.setContrast(0);
  do {
    draw();
  } 
  while( u8g.nextPage() );

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax2  =ax/16384.0;
  ay2 = ay/16384.0;
  az2 = az/16384.0;
  r = sqrt(ax2*ax2 + ay2*ay2 + az2*az2);
  itoa(int(r*10000), buffer, 10);
}



