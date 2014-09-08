/*
  Software serial multple serial test
 
 从硬件串口接收，发送到软件的序列。
 软件串行接收，发送到硬件序列。
 
 * RX是数字引脚2（连接到其他设备的TX）
 * TX是数字引脚3（连接到其他设备的RX）
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()  
{
  //打开串行通信，等待端口打开：
  Serial.begin(9600);
  while (!Serial) {
    ; // 等待串口连接。Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // 设置串口通讯的速率38400
  mySerial.begin(9600);
  Serial.println("Hello software serial!");
  // mySerial.println("Hello, world?");
}

void loop() // 循环
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available()) {
    int b = Serial.read();
    mySerial.write(b);
    if (b == '\r') {
      // Serial.print("\\r");
    } else if (b == '\n') {
      // Serial.print("\\n");
    }
  }
}

