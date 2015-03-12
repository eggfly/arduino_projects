#include <U8glib.h>
#include "Wire.h"
#include "I2Cdev.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
void draw() {
  u8g.setFont(u8g_font_unifont);
  //  u8g.drawStr( 0, 15, "Hello World!overflow line");
  u8g.drawStr( 10, 25, "Hello World! overflow line");
}

void setup() {
}
void loop() {
  u8g.firstPage();  
//  u8g.setContrast(0);
  do {
    draw();
  } 
  while( u8g.nextPage() );
}



