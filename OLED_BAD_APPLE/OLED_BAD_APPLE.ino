#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const uint8_t man_bitmap[] PROGMEM = {
  0x18,         // 00011000
  0x24,         // 00100100
  0x24,         // 00100100
  0x18,         // 00011000
  0x10,         // 00010000
  0x28,         // 00101000
  0x54,         // 01010100
  0x10,         // 00010000
  0x28,         // 00101000
  0x44,         // 01000100
};

void draw() {
  u8g.drawBitmapP(56, 55, 1, 10, man_bitmap);

}

void setup() {
}

void loop() {
  u8g.firstPage();
  do {
    draw();
  }
  while( u8g.nextPage() );
  delay(1000);
}


