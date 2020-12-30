#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

const char* ssid = "WiFi Nev";
const char* password = "WiFi kod";

WiFiUDP Udp;
IPAddress remote_IP(127.0.0.1);
unsigned int localUdpPort = 10999;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket = '1';

void setup() {
  
  Serial.begin(115200);
  ESPserial.begin(115200);
  //Serial.println();
  
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  Udp.begin(localUdpPort);
  Udp.beginPacket(Udp.remote_IP(), Udp.localUdpPort());
  Udp.write(replyPacket);
  Udp.endPacket();
  }

void loop() {
  
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
  
  if(ESPserial.available()){
    Serial.write(incomingPacket);
  }
  
}
