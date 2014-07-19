int inByte = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  // Serial.begin(9600);
  // 115200 / 10 = 11520 = 11.52KB/s
  Serial.begin(300);
  while (!Serial) {
  }
  Serial.println("initialised!");
}

void loop()
{
  int sum = 0;
  for (int i = 0; i < 256; i++){
    Serial.print("b");
  }
  sum += 256;
  Serial.println();
  Serial.println(sum);
/*
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    Serial.println(inByte);
  }
*/
}

