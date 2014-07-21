/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */
#include <SD.h>
#include <U8glib.h>
#include <MemoryFree.h>

// 1440:1080 = 11:8 ~ 12:8 = 3:2
// 10,36 -> 80:36 = 20:9
// 9,48 -> 72:48 = 3:2
// 9,42 -> 72:42 = 12:7
// 9,45 -> 72:45 = 8:5
// 8,42 -> 64:42 ~ 32:21
// 6,32 -> 48:32 = 24:16 = 3:2
// 1835 frames -> 4'33 = 273
// 3'39 = 219
#define WIDTH_COUNT 8
#define HEIGHT 42
// max: 36 * 10 = 360
#define SIZE (HEIGHT*WIDTH_COUNT)
long count = 0;
char buf[SIZE];
int left = 0, top = 0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

char timeStr[10] = "time";

File root;
File myFile;
boolean finish = false;

void draw() {
  u8g.drawBitmap(left, top, WIDTH_COUNT, HEIGHT, (const uint8_t*)buf);
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr(10, 10, timeStr);
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("START!!!");
  //  while (Serial.read() <= 0) {
  //  }

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // testPrintDir();
  // writeTest();

  Serial.print("free mem: ");
  Serial.println(freeMemory());
  readTest();
  calcArea();
}

void calcArea() {
  top = (64 - HEIGHT) / 2;
  left = (128 - WIDTH_COUNT * 8) / 2;
  if (top < 17) top = 17;
  if (left < 0) left = 0;
}
void testPrintDir() {
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");
}

void readTest() {
  char filename[] = "64x42.bin";
  myFile = SD.open(filename);
  if (myFile) {
    Serial.println(filename);
  }
}

void writeTest() {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


void loop()
{
  u8g.firstPage();
  do {
    draw();
  }
  while( u8g.nextPage() );

  if  (myFile && myFile.available() && !finish) {
    // read from the file until there's nothing else in it:
    long c = myFile.read(buf, SIZE);
    // count += c;
    // Serial.println(count);
    unsigned long ms = millis();
    dtostrf(ms/1000.0,1,2,timeStr);
    /*
    if (count > SIZE * 1000l) {
     // close the file:
     myFile.close();
     finish = true;
     Serial.println("read done.");
     }
     */
  } else {
    Serial.println("read done.");
  }
  delay(20);
}

void printDirectory(File dir, int numTabs) {
  while(true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i=0; i<numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs+1);
    } 
    else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

