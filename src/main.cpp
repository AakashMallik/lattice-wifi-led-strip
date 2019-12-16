#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <led.h>

#ifndef STASSID
#define STASSID "K-604"
#define STAPSK  "csgo4life"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int ANALOG_INPUT_PIN = A0;

ESP8266WebServer server(80);

Led led_strip(13, 12, 14, false, false);

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
        if( !server.hasArg("red") || server.arg("red") == NULL){
            server.send(400, "text/plain", "400: Red parameter missing!");
            return;
        }
        if( !server.hasArg("green") || server.arg("green") == NULL){
            server.send(400, "text/plain", "400: Green parameter missing!");
            return;
        }
        if( !server.hasArg("blue") || server.arg("blue") == NULL){
            server.send(400, "text/plain", "400: Blue parameter missing!");
            return;
        }

        int r = server.arg("red").toInt(), g = server.arg("green").toInt(), b = server.arg("blue").toInt();

        if( (0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255)){
            led_strip.handleColorChange(r, g, b);
            server.send(200, "text/plain", "Color Changed");
        }
        else{

            server.send(400, "text/plain", "Hex code range error!");
        }
    });

    server.on("/switch", HTTP_POST, [](){
        if( !server.hasArg("state") || server.arg("state") == NULL){
            server.send(400, "text/plain", "400: State parameter missing!");
            return;
        }

        server.arg("state").toInt() == 1 ? led_strip.handleSwitchOn() : led_strip.handleSwitchOff();
        
        server.send(200, "text/plain", "State changed");
    });

    server.on("/ambientmode", HTTP_POST, [](){
        if( !server.hasArg("state") || server.arg("state") == NULL){
            server.send(400, "text/plain", "400: State parameter missing!");
            return;
        }

         server.arg("state").toInt() == 1 ? led_strip.handleAmbientModeOn() : led_strip.handleAmbientModeOff();
        
        server.send(200, "text/plain", "Ambient mode changed");
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop(void) {
    if( led_strip.isAmbient() ){
        if( analogRead(ANALOG_INPUT_PIN) < 700){
            led_strip.handleSwitchOn();
        }
        else if( analogRead(ANALOG_INPUT_PIN) >= 100){
            led_strip.handleSwitchOff();
        }
    }

    server.handleClient();
    delay(500);
}
