// stl
#include <Arduino.h>

// 3rd party libs
#include <led.h>
#include <discovery.h>

// implemented header
#include <http_interface.h>

ESP8266WebServer *HttpServer::server = nullptr;

bool HttpServer::prepare(int port) {
  if(server != nullptr){
    delete server;
  }
  server = new ESP8266WebServer(port);

  server->on("/", HTTP_GET,
             []() { server->send(200, "text/plain", "Test response!"); });

  server->on("/changecolor", HTTP_POST, []() {
    if (!server->hasArg("red") || server->arg("red") == NULL) {
      server->send(400, "text/plain", "400: Red parameter missing!");
      return;
    }
    if (!server->hasArg("green") || server->arg("green") == NULL) {
      server->send(400, "text/plain", "400: Green parameter missing!");
      return;
    }
    if (!server->hasArg("blue") || server->arg("blue") == NULL) {
      server->send(400, "text/plain", "400: Blue parameter missing!");
      return;
    }

    int r = server->arg("red").toInt(), g = server->arg("green").toInt(),
        b = server->arg("blue").toInt();

    if ((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255)) {
      Led::handleColorChange(r, g, b);
      server->send(200, "text/plain", "Color Changed");
    } else {

      server->send(400, "text/plain", "Hex code range error!");
    }
  });

  server->on("/switch", HTTP_POST, []() {
    if (!server->hasArg("state") || server->arg("state") == NULL) {
      server->send(400, "text/plain", "400: State parameter missing!");
      return;
    }

    server->arg("state").toInt() == 1 ? Led::handleSwitchOn()
                                      : Led::handleSwitchOff();

    server->send(200, "text/plain", "State changed");
  });

  server->on("/ambientmode", HTTP_POST, []() {
    if (!server->hasArg("state") || server->arg("state") == NULL) {
      server->send(400, "text/plain", "400: State parameter missing!");
      return;
    }

    server->arg("state").toInt() == 1 ? Led::handleAmbientModeOn()
                                      : Led::handleAmbientModeOff();

    server->send(200, "text/plain", "Ambient mode changed");
  });

  server->on("/attach", HTTP_POST, []() {
    if (!server->hasArg("ip") || server->arg("ip") == NULL) {
      server->send(400, "text/plain", "400: ip parameter missing!");
      return;
    }
    if (!server->hasArg("port") || server->arg("port") == NULL) {
      server->send(400, "text/plain", "400: port parameter missing!");
      return;
    }

    Discovery::isAttached = true;

    server->send(200, "text/plain", "Device attached successfully");
  });

  server->on("/detach", HTTP_POST, []() {
    Discovery::isAttached = false;

    server->send(200, "text/plain", "Device detached successfully");
  });

  server->begin();
  Serial.println("HTTP server started");
  return true;
}

bool HttpServer::listen() {
  server->handleClient();
  return true;
}