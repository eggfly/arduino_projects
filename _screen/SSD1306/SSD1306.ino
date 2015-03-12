#include <U8glib.h>
char buffer[16];
// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SSD1306_128X64 u8g(13,11,10,9,8);
int i = 0;
void draw() {
  u8g.setFont(u8g_font_unifont);
  //u8g.drawStr( 0, 15, "Hello World!overflow line");
  u8g.drawStr(30,45, buffer);
  //u8g.drawStr(40,45, "frames");
}

void setup() {
}

void loop() {
  u8g.firstPage();  
  do {
    draw();
  } 
  while( u8g.nextPage() );
  itoa(i, buffer, 10);
  i++;
  //  delay(1000);
}


