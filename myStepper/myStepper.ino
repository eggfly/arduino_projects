#define PIN_A 8
#define PIN_B 9
#define PIN_C 10
#define PIN_D 11
#define STEP_COUNT 8
// AB BC CD DA
void setup() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_D, OUTPUT);
}

int step = 0; // 0,1,2,3
void manipulate(){
  switch(step) {
  case 0:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, LOW);
    break;
  case 1:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
    digitalWrite(PIN_D, LOW);
    break;
  case 2:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, LOW);
    digitalWrite(PIN_D, HIGH);
    break;
  case 3:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, LOW);
    digitalWrite(PIN_D, HIGH);
    break;
  case 4:
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, HIGH);
    break;
  case 5:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, HIGH);
    break;
  case 6:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, HIGH);
    break;
  case 7:
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    digitalWrite(PIN_C, HIGH);
    digitalWrite(PIN_D, LOW);
    break;
  }
  if (step < 0) {
    step+=STEP_COUNT;
  }
  step%=STEP_COUNT;
}
void nextStep() {
  step++;
  manipulate();
}
void previousStep() {
  step--;
  manipulate();
}
void loop() {
  int i = 0;
  for(i=0;i<1000;i++){
    nextStep();
    delay(5);
  }
  for(i=0;i<1000;i++){
    previousStep();
    delay(5);
  }
}






