#include <MemoryFree.h>
void setup(){
  Serial.begin(9600);
  Serial.println(freeMemory());

}
void loop(){
}



