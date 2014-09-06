int pushButton = 2;
long spd = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  attachInterrupt(0, blink, RISING);
}


void loop()
{
  delay(1000);
  Serial.println(spd);
  Serial.println("viberate!");
  spd = 0;
}

void blink()
{
//  detachInterrupt(0);
//  delay(200);
//  attachInterrupt(0, blink, RISING);
  spd ++;
}

