#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
 #define OLED_DC     6
 #define OLED_CS     7
 #define OLED_RESET  8
 Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
 */

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// dust sensor
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
// end of dust sensor

void setup() {             
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // display.display();
  // delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  //  display.setTextSize(1);
  //  display.setTextColor(WHITE);
  //  display.setCursor(0,0);
  //  display.println("Hello, world!");
  //  display.setTextColor(BLACK, WHITE); // 'inverted' text
  //  display.println(3.141592);
  //  display.setTextSize(2);
  //  display.setTextColor(WHITE);
  //  display.print("0x"); 
  //  display.println(0xDEADBEEF, HEX);
  //  display.display();
  //  delay(2000);
}

int pages = 0;
const int SIZE = 10;
const int DATA_PARTS = 8;
void loop() {
  float dustDensity = sampling();

  if (pages % SIZE < DATA_PARTS) {
    drawData(dustDensity);
  } 
  else {
    drawText();
  }
  pages ++;
  if (pages >= SIZE) {
    pages = 0;
  }
}

void drawText() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("PM2.5 levels:");
  display.println();

  display.println("Good  :   0-35 ug/m3");
  display.println("OK    :  35-75 ug/m3");
  display.println("Light :  7-115 ug/m3");
  display.println("Middle:115-150 ug/m3");
  display.println("Severe:150-250 ug/m3");
  display.println("Serious: > 250 ug/m3");

  display.display();
}
void drawData(float dustDensity) {
  if (dustDensity < 0) {
    dustDensity = 0;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("PM2.5 level(1-6): ");
  int ug = dustDensity * 1000;
  int level = 0;
  if (ug < 35) {
    level = 1;
  } 
  else if (ug < 75) {
    level = 2;
  } 
  else if (ug < 115) {
    level = 3;
  } 
  else if (ug < 150) {
    level = 4;
  } 
  else if (ug < 250) {
    level = 5;
  } 
  else {
    level = 6;
  }
  display.print(level);

  display.setTextSize(3);
  display.setCursor(20,12);
  display.print(ug);

  display.setTextSize(1);
  display.setCursor(95,25);
  display.print("ug/m3");

  display.setTextSize(3);
  display.setCursor(20,40);
  display.print(dustDensity);

  display.setTextSize(1);
  display.setCursor(95,54);
  display.print("mg/m3");

  display.display();
}
float sampling(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  // Serial.print("Raw Signal Value (0-1023): ");
  // Serial.print(voMeasured);

  // Serial.print(" - Voltage: ");
  // Serial.print(calcVoltage);

  // Serial.print(" - Dust Density: ");
  // Serial.print(dustDensity); // unit: mg/m3
  // Serial.print(" mg/m3, "); // unit: mg/m3

  // Serial.print(int(ret)); // unit: mg/m3
  // Serial.println(" ug/m3"); // unit: mg/m3
  Serial.println(dustDensity * 1000.0); // unit: mg/m3
  delay(1000);
  return dustDensity;
}

