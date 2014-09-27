#include <EtherCard.h>
static byte mymac[] = {0x74,0x69,0x69,0x2D,0x30,0x31};
static byte myip[] = {192,168,1,249};
byte Ethernet::buffer[700];
static uint32_t timer; 
void setup () {
 
  Serial.begin(9600);
  Serial.println("PING Demo");
 
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0)
    Serial.println( "Failed to access Ethernet controller");
 
  if (!ether.staticSetup(myip))
    Serial.println("Failed to set IP address");
}
 
void loop() {
//  ether.packetReceive();
//  ether.packetLoop();
  word len = ether.packetReceive(); // go receive new packets
  word pos = ether.packetLoop(len); // respond to incoming pings
  Serial.println(pos);
}

