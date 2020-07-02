// arduino libs
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// 3rd party libs
#include <led.h>

// modules
#include <http_interface.h>

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

  Led::prepare(14, 13, 12, false, true);
  HttpServer::prepare(80);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop(void) {
  // if (Led::isAmbient()) {
  //   int voltage_value = analogRead(ANALOG_INPUT_PIN);
  //   if (voltage_value >= 100) {
  //     Led::handleSwitchOff();
  //   } else {
  //     Led::handleSwitchOn();
  //   }
  //   delay(250);
  // }

  HttpServer::listen();
}
