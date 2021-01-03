#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(1, 5);

const char* ssid = "Tenda_2731F0";
const char* password = "12345678";

WiFiUDP Udp;
unsigned int localUdpPort = 10999;  // local port to listen on
int messagePacket;  // buffer for incoming packets

void setup() {
  
  Serial.begin(9600);
  ESPserial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

 
  //Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  //Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

}

void loop() {
  if(Serial.available()){
  messagePacket = Serial.read(); 
  if(messagePacket=='1')
  {
     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(messagePacket);
  Udp.endPacket();
  }
}
