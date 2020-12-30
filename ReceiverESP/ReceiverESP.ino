#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

const char* ssid = "WiFi Nev";
const char* password = "WiFi kod";

WiFiUDP Udp;
unsigned int localUdpPort = 10999;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket = '1';

void setup() {
  
  Serial.begin(115200);
  ESPserial.begin(115200);
  //Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println(" connected");

  Udp.begin(localUdpPort);
  //Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(replyPacket);
  Udp.endPacket();
  }

void loop() {
  
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
  
  //Serial.printf("UDP packet contents: %s\n", incomingPacket);
  if(ESPserial.available()){
    Serial.write(incomingPacket);
  }
  
}
