/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */

#include <SD.h>

File myFile;
char bytes[1024];
int offset = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);


  Serial.println("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    delay(1000);
    return;
  }
  Serial.println("initialization done.");

// re-open the file for reading:
  myFile = SD.open("HyperChem.rar");
//  if (myFile) {
//    Serial.println("HyperChem.rar:");
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      myFile.read(bytes, 1024);
//      offset += 1024;
//      Serial.println(offset);
//    }
//    // close the file:
//    myFile.close();
//  } 
//  else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
}

void loop()
{
  // nothing happens after setup
}


