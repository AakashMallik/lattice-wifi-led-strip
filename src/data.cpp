// stl
#include <ESP8266WiFi.h>

// implementation header
#include <data.h>

// internal module
#include <http_interface.h>

DynamicJsonDocument *Data::doc_udp = nullptr;
DynamicJsonDocument *Data::doc_http = nullptr;

void Data::prepare() {
  doc_udp = new DynamicJsonDocument(200);
  doc_http = new DynamicJsonDocument(200);

  // data udp becon
  (*doc_udp)["id"] = WiFi.macAddress();
  (*doc_udp)["link"] =
      "http://" + WiFi.localIP().toString() + ":" + HttpServer::PORT;
  (*doc_udp)["type"] = "light";
  (*doc_udp)["title"] = "Radlet Plankton";
  (*doc_udp)["description"] =
      "A cute LED wifi controlled strip that can take upto 16 million colors";

  // data http device registration
  (*doc_http)["id"] = WiFi.macAddress();
  (*doc_http)["link"] = WiFi.localIP().toString() + ":" + HttpServer::PORT;
  (*doc_http)["type"] = "light";
  (*doc_http)["title"] = "light";
  (*doc_http)["description"] = "light";
}

String Data::generateUdpPayload() {
  String udp_payload;
  serializeJson(*doc_udp, udp_payload);
  return udp_payload;
}

String Data::generateHTTPPayload() {
  String http_payload;
  serializeJson(*doc_http, http_payload);
  return http_payload;
}