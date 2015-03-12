#include <Wire.h>

unsigned char frequencyH = 0;
unsigned char frequencyL = 0;

unsigned int frequencyB;
double frequency = 0;

void setup()
{
  Wire.begin();
  frequency = 93.0; //starting frequency
  setFrequency();
  Serial.begin(9600);
}

void loop()
{
  int reading = analogRead(0);
  //frequency = map((float)reading, 0.0, 1024.0, 87.5, 108.0);
 
  frequency = ((double)reading * (108.0 - 87.5)) / 1024.0 + 87.5;
  frequency = ((int)(frequency * 10)) / 10.0;
 
  setFrequency();
  //Serial.println(frequency);
}

void setFrequency()
{
  frequencyB = 4 * (frequency * 1000000 + 225000) / 32768;
  frequencyH = frequencyB >> 8;
  frequencyL = frequencyB & 0XFF;
  delay(100);
  Wire.beginTransmission(0x60);
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  delay(100); 
}
