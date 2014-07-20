#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
#define MENU_ITEMS 4
char *menu_strings[MENU_ITEMS] = { 
  "First Line", "Second Item", "3333333", "abcdefg" };
uint8_t menu_current = 0;
void draw_menu() {
  uint8_t i, h;
  u8g_uint_t w, d;
  u8g.setFont(u8g_font_7x13O);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  w = u8g.getWidth();
  for( i = 0; i < MENU_ITEMS; i++ ) {        // draw all menu items
    d = (w-u8g.getStrWidth(menu_strings[i]))/2;
    u8g.setDefaultForegroundColor();
    if ( i == menu_current ) {               // current selected menu item
      u8g.drawBox( 0, i*h+1, w, h);     // draw cursor bar
      u8g.setDefaultBackgroundColor();
    }
    u8g.drawStr(d, i*h, menu_strings[i]);
  }
}

void setup() {
}

void loop() {
  u8g.firstPage();
  do {
    draw_menu();
  } 
  while( u8g.nextPage() );
  delay(1000);
}

