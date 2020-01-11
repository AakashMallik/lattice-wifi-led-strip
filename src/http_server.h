#ifndef HTTP_SERVER
#define HTTP_SERVER

// ardunio libs
#include <ESP8266WebServer.h>

// 3rd party libs
#include <led.h>

class HttpServer {
  ESP8266WebServer server;
  Led * led_strip_ptr;

public:
  HttpServer(int port, Led &led_strip_ptr);
  bool prepare();
  bool listen();
};

#endif