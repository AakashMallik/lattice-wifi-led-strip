// stl
#include <Arduino.h>
#include <ESP8266WiFi.h>

// 3rd party lib
#include <ArduinoJson.h>

// internal module
#include <data.h>
#include <http_interface.h>

// implemented header
#include <udp_interface.h>

AsyncUDP *UdpInterface::udp = nullptr;

bool UdpInterface::prepare(int a, int b, int c, int d, int multicast_port) {
  if (udp != nullptr) {
    delete udp;
  }
  udp = new AsyncUDP();

  if (udp->listenMulticast(IPAddress(a, b, c, d), multicast_port)) {
    udp->onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast()
                       ? "Broadcast"
                       : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      // reply to the client
      // packet.printf("Got %u bytes of data", packet.length());
    });
    return true;
  } else {
    Serial.println("Could not bind to udp port");
    return false;
  }
}

bool UdpInterface::broadcast() {
  // StaticJsonDocument<150> doc;
  // doc["mac"] = WiFi.macAddress();
  // doc["ip"] = WiFi.localIP().toString();
  // doc["port"] = HttpServer::PORT;
  // String udp_payload;
  // serializeJson(doc, udp_payload);
  udp->print(Data::generateUdpPayload());
  return true;
}