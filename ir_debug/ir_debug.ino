//本例来自于红外接收模块的IRremote自带范例
/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * [url]http://arcfn.com[/url]
 */

#include <IRremote.h>

int RECV_PIN = 11;//定义红外接收器的引脚为11
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 初始化红外接收器
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long value = results.value;
    switch(value) {
    case 0xFD00FF:
      Serial.println("power");
      break;
    case 0xFFFFFFFF:
      Serial.println("empty");
      break;
      case 0xFD807F:
      Serial.println("VOL+");
      break;
      case 0xFD906F:
      Serial.println("VOL-");
      break;
      case 0xFD40BF:
      Serial.println("FUNC/STOP");
      break;
      case 0xFD20DF:
      Serial.println("PREV");
      break;
      case 0xFD609F:
      Serial.println("NEXT");
      break;
      case 0xFDA05F:
      Serial.println("PLAY/PAUSE");
      break;
      case 0xFD10EF:
      Serial.println("DOWN");
      break;
      case 0xFD50AF:
      Serial.println("UP");
      break;
      case 0xFDB04F:
      Serial.println("EQ");
      break;
      case 0xFD708F:
      Serial.println("ST/REPT");
      break;
      case 0xFD30CF:
      Serial.println("0");
      break;
      case 0xFD08F7:
      Serial.println("1");
      break;
      case 0xFD8877:
      Serial.println("2");
      break;
      case 0xFD48B7:
      Serial.println("3");
      break;
      case 0xFD28D7:
      Serial.println("4");
      break;
      case 0xFDA857:
      Serial.println("5");
      break;
      case 0xFD6897:
      Serial.println("6");
      break;
      case 0xFD18E7:
      Serial.println("7");
      break;
      case 0xFD9867:
      Serial.println("8");
      break;
      case 0xFD58A7:
      Serial.println("9");
      break;
    default:
      Serial.println(results.value, HEX);//以16进制换行输出接收代码
      break;
    }
    // Serial.println();//为了便于观看输出结果增加一个空行
    irrecv.resume(); // 接收下一个值
  }
}




