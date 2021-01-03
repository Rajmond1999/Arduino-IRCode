#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3);

const char* ssid = "Tenda_2731F0";
const char* password = "12345678";

WiFiUDP Udp;
unsigned int localUdpPort = 10999;  // local port to listen on
char incomingPacket[4];  // buffer for incoming packets


void setup() {
  
  Serial.begin(9600);
  ESPserial.begin(115200);
  //Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println(" connected");
  digitalWrite(LED_BUILTIN,LOW);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  
  }

void loop() {
  
  int packetSize = Udp.parsePacket();

  
  if (packetSize)
  {
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 4);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      delay(500);
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
        if(Serial.available()){
    Serial.write(incomingPacket);
  }
  
    }
  }
}
