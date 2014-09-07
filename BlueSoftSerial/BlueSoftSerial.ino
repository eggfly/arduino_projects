#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 2  //for Leonardo：10
#define TxD 3  //for Leonardo：11
//对菜鸟重要：
//for UNO D2 应连接蓝牙模块上的TXD
//        D3 应连接蓝牙模块上的RTD
//  可以理解为上述define是对主板而言的，因为SoftwareSerial库可是在主板上运行的哦，RX自然要对接TX。

#define LED 13

SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
  Serial.begin(9600);         
  pinMode(LED, OUTPUT);

  setupBlueToothConnection();
}

void loop()
{
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);       
}

void setupBlueToothConnection()
{
  Serial.println("Setting Bluetooth parameters");      
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  delay(100);
  sendBlueToothCommand("AT\r\n");
  sendBlueToothCommand("AT+NAME?\r\n");//命名模块名
  sendBlueToothCommand("AT+RNAME?\r\n");//命名模块名
  sendBlueToothCommand("AT+ROLE?\r\n");//命名模块名
  sendBlueToothCommand("AT+PSWD?\r\n");//命名模块名
  sendBlueToothCommand("AT+STATE?\r\n");//命名模块名
  //sendBlueToothCommand("AT+NAME=HC-05\r\n");//命名模块名
  //sendBlueToothCommand("AT+ROLE=0\r\n");//设置主从模式：0从机，1主机
  sendBlueToothCommand("AT+ADDR?\r\n");//设置主从模式：0从机，1主机
  //sendBlueToothCommand("AT+PSWD=1234\r\n");//设置配对密码，如0123
  sendBlueToothCommand("AT+UART?\r\n");//设置波特率9600，停止位1，校验位无
  //sendBlueToothCommand("AT+UART=38400,0,0\r\n");//设置波特率9600，停止位1，校验位无
  //sendBlueToothCommand("AT+RMAAD\r\n");//清空配对列表
  delay(100);
  Serial.println("Setup complete");
}
void sendBlueToothCommand(char command[])
{
  char a;
  blueToothSerial.print(command);
  Serial.print(command);                       
  delay(100);
  while(blueToothSerial.available())           
  {                                               
    Serial.print(char(blueToothSerial.read()));
  }                                            
}

