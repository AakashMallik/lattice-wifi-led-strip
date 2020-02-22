// arduino libs
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// 3rd party libs
#include <led.h>

// modules
#include <inbuilt_led_interface.h>
#include <discovery.h>
#include <data.h>
#include <http_interface.h>
#include <udp_interface.h>

// SSID and PASSWORD
#ifndef STASSID
#define STASSID "K-604"
#define STAPSK "csgo4life"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

const int ANALOG_INPUT_PIN = A0;

void setup(void) {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("|");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Data::prepare();
  InbuiltLedInterface::prepare();
  Led::prepare(13, 12, 14, false, false);
  HttpServer::prepare(80);
  UdpInterface::prepare(239, 255, 0, 1, 30001);
}

void loop(void) {
  if (Led::isAmbient()) {
    int voltage_value = analogRead(ANALOG_INPUT_PIN);
    if (voltage_value >= 100) {
      Led::handleSwitchOff();
    } else {
      Led::handleSwitchOn();
    }
    delay(250);
  }

  if (!Discovery::isAttached) {
    UdpInterface::broadcast();
    InbuiltLedInterface::playPattern( 2500, 1 );
  }

  HttpServer::listen();
}
