/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */
#include <SD.h>
#include <U8glib.h>

#define BLOCK 10
long count = 0;
char buf[BLOCK];

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

File root;
File myFile;
int pos = 5;
boolean finish = false;

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
  u8g.drawBitmapP(56, 40 + pos, 1, 10, man_bitmap);
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  Serial.print("START!!!");
  while (Serial.read() <= 0) {}

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

  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");

  // writeTest();
  readTest();
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
  pos = -pos;

  if  (myFile && myFile.available() && !finish) {
    // read from the file until there's nothing else in it:
    long c = myFile.read(buf, BLOCK);
    count += c;
    Serial.println(count);
    if (count > BLOCK * 100l) {
      // close the file:
      myFile.close();
      finish = true;
      Serial.println("read done.");
    }
  }
  delay(1000);
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

