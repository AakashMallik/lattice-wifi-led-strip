#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Tower K Free Wifi"
#define STAPSK  "csgo4life"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int CONTROLLER_PIN_RED = 13; //D7
const int CONTROLLER_PIN_GREEN = 12; //D6
const int CONTROLLER_PIN_BLUE = 14; //D5
const int ANALOG_INPUT_PIN = A0;

bool STATE_RED = false;
bool STATE_GREEN = true;
bool STATE_BLUE = true;

bool STATE_ON = false;

bool AMBIENT_MODE = true;

ESP8266WebServer server(80);

void handleTestUrl() {
    server.send(200, "text/plain", "Test response!");
}

void handleToggleAmbientMode(){
    AMBIENT_MODE = !AMBIENT_MODE;
}

void applyChange(){
    if( STATE_ON ){
        digitalWrite(CONTROLLER_PIN_RED, STATE_RED ? HIGH : LOW);
        digitalWrite(CONTROLLER_PIN_GREEN, STATE_GREEN ? HIGH : LOW);
        digitalWrite(CONTROLLER_PIN_BLUE, STATE_BLUE ? HIGH : LOW);
    }
    else{
        digitalWrite(CONTROLLER_PIN_RED, LOW);
        digitalWrite(CONTROLLER_PIN_GREEN, LOW);
        digitalWrite(CONTROLLER_PIN_BLUE, LOW);
    }
}


void handleColorChange(){
    if( !server.hasArg("code") || server.arg("code") == NULL){
        server.send(400, "text/plain", "400: Invalid Request");
        return;
    }

    Serial.println(server.arg("code"));
    switch (server.arg("code").toInt())
    {
    case 0:
        STATE_RED = true;
        STATE_GREEN = true;
        STATE_BLUE = true;
        break;
    case 1:
        STATE_RED = true;
        STATE_GREEN = true;
        STATE_BLUE = false;
        break;
    case 2:
        STATE_RED = false;
        STATE_GREEN = true;
        STATE_BLUE = true;
        break;
    case 3:
        STATE_RED = true;
        STATE_GREEN = false;
        STATE_BLUE = true;
        break;
    case 4:
        STATE_RED = true;
        STATE_GREEN = false;
        STATE_BLUE = false;
        break;
    case 5:
        STATE_RED = false;
        STATE_GREEN = false;
        STATE_BLUE = true;
        break; 
    case 6:
        STATE_RED = false;
        STATE_GREEN = true;
        STATE_BLUE = false;
        break;    
    default:
        break;
    }
    
    STATE_ON = true;

    applyChange();
    server.send(200, "text/plain", "Color Changed");
}

void handleToggleState(){
    STATE_ON = !STATE_ON;
    
    applyChange();
    server.send(200, "text/plain", "State toggled");
}

void setup(void) {
    Serial.begin(115200);

    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(CONTROLLER_PIN_RED, OUTPUT);
    pinMode(CONTROLLER_PIN_GREEN, OUTPUT);
    pinMode(CONTROLLER_PIN_BLUE, OUTPUT);
  
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
    if( analogRead(ANALOG_INPUT_PIN) < 700 && AMBIENT_MODE){
        STATE_ON = true;
        applyChange();
    }
    else if( analogRead(ANALOG_INPUT_PIN) >= 100 && AMBIENT_MODE ){
        STATE_ON = false;
        applyChange();
    }
    server.handleClient();
    MDNS.update();
}
