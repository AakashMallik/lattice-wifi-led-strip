#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <led.h>

#ifndef STASSID
#define STASSID "Tower K Free Wifi"
#define STAPSK  "csgo4life"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int ANALOG_INPUT_PIN = A0;

ESP8266WebServer server(80);

Led led_strip(13, 12, 14, true, false);

void setup(void) {
    Serial.begin(115200);
    
    led_strip.begin();

    pinMode(LED_BUILTIN, OUTPUT);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    digitalWrite(LED_BUILTIN, LOW);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("|");
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](){
        server.send(200, "text/plain", "Test response!");
    });

    server.on("/changecolor", HTTP_POST, [](){
        if( !server.hasArg("code") || server.arg("code") == NULL){
            server.send(400, "text/plain", "400: Invalid Request");
            return;
        }
        Serial.println(server.arg("code").toInt());
        led_strip.handleColorChange(server.arg("code").toInt());
        server.send(200, "text/plain", "Color Changed");
    });

    server.on("/togglestate", HTTP_GET, [](){
        led_strip.handleToggleState();
        server.send(200, "text/plain", "State toggled");
    });

    server.on("/toggleambientmode", HTTP_GET, [](){
        led_strip.handleToggleAmbientMode();
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop(void) {
    if( led_strip.isAmbient() ){
        if( analogRead(ANALOG_INPUT_PIN) < 700){
            led_strip.handleToggleState(true);
        }
        else if( analogRead(ANALOG_INPUT_PIN) >= 100){
            led_strip.handleToggleState(false);
        }
    }

    server.handleClient();
    delay(500);
}
