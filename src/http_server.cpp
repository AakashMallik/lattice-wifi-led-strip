#include <Arduino.h>

#include <http_server.h>

HttpServer::HttpServer(int port, Led &led)
    : server(port), led_strip_ptr(&led) {}

bool HttpServer::prepare() {
  led_strip_ptr->begin();

  server.on("/", HTTP_GET,
            [this]() { server.send(200, "text/plain", "Test response!"); });

  server.on("/changecolor", HTTP_POST, [this]() {
    if (!server.hasArg("red") || server.arg("red") == NULL) {
      server.send(400, "text/plain", "400: Red parameter missing!");
      return;
    }
    if (!server.hasArg("green") || server.arg("green") == NULL) {
      server.send(400, "text/plain", "400: Green parameter missing!");
      return;
    }
    if (!server.hasArg("blue") || server.arg("blue") == NULL) {
      server.send(400, "text/plain", "400: Blue parameter missing!");
      return;
    }

    int r = server.arg("red").toInt(), g = server.arg("green").toInt(),
        b = server.arg("blue").toInt();

    if ((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255)) {
      led_strip_ptr->handleColorChange(r, g, b);
      server.send(200, "text/plain", "Color Changed");
    } else {

      server.send(400, "text/plain", "Hex code range error!");
    }
  });

  server.on("/switch", HTTP_POST, [this]() {
    if (!server.hasArg("state") || server.arg("state") == NULL) {
      server.send(400, "text/plain", "400: State parameter missing!");
      return;
    }

    server.arg("state").toInt() == 1 ? led_strip_ptr->handleSwitchOn()
                                     : led_strip_ptr->handleSwitchOff();

    server.send(200, "text/plain", "State changed");
  });

  server.on("/ambientmode", HTTP_POST, [this]() {
    if (!server.hasArg("state") || server.arg("state") == NULL) {
      server.send(400, "text/plain", "400: State parameter missing!");
      return;
    }

    server.arg("state").toInt() == 1 ? led_strip_ptr->handleAmbientModeOn()
                                     : led_strip_ptr->handleAmbientModeOff();

    server.send(200, "text/plain", "Ambient mode changed");
  });

  server.begin();
  Serial.println("HTTP server started");
  return true;
}

bool HttpServer::listen() {
  server.handleClient();
  return true;
}