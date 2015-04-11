#include <U8glib.h>

char incomingByte;  // incoming data
int  LED = 13;      // LED pin
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
char fpsStr[32];
char uptimeStr[16];
unsigned long t = 0;
unsigned long lastRefreshClockTime = 0;
static char buffer[16];

int led = 13;
int ledState = HIGH;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  Serial.begin(115200); // initialization
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // remove
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH); // remove
  Serial.println("Hello remote control!");
}

void draw() {
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr(80, 10, fpsStr);
  u8g.drawStr(50, 28, "uptime:");
  u8g.drawStr(50, 38, uptimeStr);
  u8g.drawStr(10, 10, buffer);
  u8g.drawFrame(0,0,128,64);
  u8g.drawFrame(100,20, 20,40);
  u8g.drawBitmapP( 106, 35, 1, 10, man_bitmap);
  u8g.drawXBMP( 5, 30, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
}
void loop (){
  handleBT();
  lcd();
}
int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
    case '\n': // Ignore new-lines
      break;
    case '\r': // Return on CR
    case ' ':
      rpos = pos;
      pos = 0;  // Reset position index ready for next time
      return rpos;
    default:
      if (pos < len-1) {
        buffer[pos++] = readch;
        buffer[pos] = 0;
      }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

#define CMD_Echo '1'
#define CMD_Vibration '2'
#define CMD_Blink '3'

void handleBT() {
  if (readline(Serial.read(), buffer, 16) > 0) {
    Serial.print("You entered: >");
    Serial.print(buffer);
    Serial.println("<");
  }
  //  if (Serial.available() > 0) {  // if the data came
  //    incomingByte = Serial.read(); // read byte
  //    if(incomingByte == '0') {
  //      digitalWrite(LED, LOW);  // if 1, switch LED Off
  //      Serial.println("LED OFF. Press 1 to LED ON!");  // print message
  //    }
  //    if(incomingByte == '1') {
  //      digitalWrite(LED, HIGH); // if 0, switch LED on
  //      Serial.println("LED ON. Press 0 to LED OFF!");
  //    }
  //  }
}
void lcd() {
  // led
  // digitalWrite(led, ledState);   // turn the LED on (HIGH is the voltage level)
  // ledState = !ledState;

  u8g.firstPage();  
  do {
    draw();
  }
  while( u8g.nextPage() );
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
    /* refresh褰撳墠鏃堕棿 */
  }
}



