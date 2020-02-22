#ifndef DATA
#define DATA

// stl
#include <Arduino.h>

// 3rd party lib
#include <ArduinoJson.h>

class Data {
  static DynamicJsonDocument *doc_udp;
  static DynamicJsonDocument *doc_http;

public:
  static void prepare();
  static String generateUdpPayload();
  static String generateHTTPPayload();
};

#endif