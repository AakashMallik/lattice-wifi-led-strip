#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
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

void handleTestUrl() {
    server.send(200, "text/plain", "Test response!");
}

void handleToggleAmbientMode(){
    led_strip.handleToggleAmbientMode();
}

void handleColorChange(){
    if( !server.hasArg("code") || server.arg("code") == NULL){
        server.send(400, "text/plain", "400: Invalid Request");
        return;
    }
    Serial.println(server.arg("code").toInt());
    led_strip.handleColorChange(server.arg("code").toInt());
    server.send(200, "text/plain", "Color Changed");
}

void handleToggleState(){
    led_strip.handleToggleState();
    server.send(200, "text/plain", "State toggled");
}

void setup(void) {
    Serial.begin(115200);
    
    led_strip.begin();

    pinMode(BUILTIN_LED, OUTPUT);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    digitalWrite(BUILTIN_LED, LOW);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("|");
    }
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", HTTP_GET, handleTestUrl);
    server.on("/changecolor", HTTP_POST, handleColorChange);
    server.on("/togglestate", HTTP_GET, handleToggleState);
    server.on("/toggleambientmode", HTTP_GET, handleToggleAmbientMode);

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
    MDNS.update();
}
