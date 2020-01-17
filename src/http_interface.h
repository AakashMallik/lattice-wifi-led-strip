#ifndef HTTP_SERVER
#define HTTP_SERVER

// ardunio libs
#include <ESP8266WebServer.h>

class HttpServer {
  static ESP8266WebServer *server;

public:
  static bool prepare(int port);
  static bool listen();
};

#endif