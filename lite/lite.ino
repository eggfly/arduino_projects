#include <U8glib.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
//#include <stdio.h>
//#include <string.h>
#include <DS1302.h>

/* 接口定义
 CE(DS1302 pin5) -> Arduino D5
 IO(DS1302 pin6) -> Arduino D6
 SCLK(DS1302 pin7) -> Arduino D7
 */
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

const uint8_t cocktail[] PROGMEM = {
  0x0 ,0x0 ,0x0 ,0x7e,0xff,
  0xff,0x0 ,0x0 ,0x0 ,0xff,
  0xff,0xff,0xff,0xff,0xff,
};
#define u8g_logo_width 38
#define u8g_logo_height 24

static unsigned char u8g_logo_bits[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
  0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
  0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
  0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
  0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
  0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
  0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
  0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
  0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
  0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f
};

const uint8_t rook_bitmap[] PROGMEM = {
  0x00,         // 00000000
  0x55,         // 01010101
  0x7f,         // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x3e,         // 00111110
  0x7f          // 01111111
};

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

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  accelgyro.initialize();
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
}

void draw() {
  u8g.setFont(u8g_font_6x12);
//  u8g.drawStr(3, 10, time);
//  u8g.drawStr(3, 19, date);
  u8g.drawStr(80, 10, fpsStr);
  //  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(50, 28, "uptime:");
  u8g.drawStr(50, 38, uptimeStr);
  u8g.drawStr(50, 48, "acc(g):");
  u8g.drawStr(50, 58, accStr);
  u8g.drawFrame(0,0,128,64);
  u8g.drawFrame(100,20, 20,40);
  u8g.drawBitmapP( 106, 55-(int)(r*20), 1, 10, man_bitmap);
  u8g.drawXBMP( 5, 30, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
}

void loop() {
  // led
  digitalWrite(led, ledState);   // turn the LED on (HIGH is the voltage level)
  ledState = !ledState;

  u8g.firstPage();  
  u8g.setContrast(0);
  do {
    draw();
  }
  while( u8g.nextPage() );
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
//    query_time();
  }
//  readTime();
}


