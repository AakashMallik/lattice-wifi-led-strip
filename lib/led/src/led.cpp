#include <led.h>
#include <Arduino.h>

Led::Led(int red_pin,  int green_pin, int blue_pin, bool is_ambient_on, bool initial_state):
    CONTROLLER_PIN_RED(red_pin),
    CONTROLLER_PIN_GREEN(green_pin),
    CONTROLLER_PIN_BLUE(blue_pin),
    AMBIENT_MODE(is_ambient_on),
    STATE_ON(initial_state),
    DC_RED(0),
    DC_GREEN(0),
    DC_BLUE(0)
{
    applyChange();
}

Led::~Led(){

}

bool Led::begin(){
    pinMode(CONTROLLER_PIN_RED, OUTPUT);
    pinMode(CONTROLLER_PIN_GREEN, OUTPUT);
    pinMode(CONTROLLER_PIN_BLUE, OUTPUT);
}

bool Led::handleAmbientModeOn(){
    AMBIENT_MODE = true;
}

bool Led::handleAmbientModeOff(){
    AMBIENT_MODE = false;
}


bool Led::handleSwitchOn(){
    STATE_ON = true;
    
    return applyChange();
}

bool Led::handleSwitchOff(){
    STATE_ON = false;
    
    return applyChange();
}

bool Led::handleColorChange(int r, int g, int b){
    DC_RED = (int)(( (float)r / 255 ) * 1024);
    DC_GREEN = (int)(( (float)g / 255 ) * 1024);
    DC_BLUE = (int)(( (float)b / 255 ) * 1024);

    return applyChange();
}

const bool Led::isAmbient(){
    return AMBIENT_MODE;
}

bool Led::applyChange(){
    if( STATE_ON ){
        analogWrite(CONTROLLER_PIN_RED, DC_RED);
        analogWrite(CONTROLLER_PIN_GREEN, DC_GREEN);
        analogWrite(CONTROLLER_PIN_BLUE, DC_BLUE);
    }
    else{
        digitalWrite(CONTROLLER_PIN_RED, LOW);
        digitalWrite(CONTROLLER_PIN_GREEN, LOW);
        digitalWrite(CONTROLLER_PIN_BLUE, LOW);
    }

    return true;
}