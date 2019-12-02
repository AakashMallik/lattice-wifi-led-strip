#include <led.h>
#include <Arduino.h>

Led::Led(int red_pin,  int green_pin, int blue_pin, bool is_ambient_on, bool initial_state):
    CONTROLLER_PIN_RED(red_pin),
    CONTROLLER_PIN_GREEN(green_pin),
    CONTROLLER_PIN_BLUE(blue_pin),
    AMBIENT_MODE(is_ambient_on),
    STATE_ON(initial_state),
    STATE_RED(true),
    STATE_GREEN(true),
    STATE_BLUE(false)
{

}

Led::~Led(){

}

bool Led::begin(){
    pinMode(CONTROLLER_PIN_RED, OUTPUT);
    pinMode(CONTROLLER_PIN_GREEN, OUTPUT);
    pinMode(CONTROLLER_PIN_BLUE, OUTPUT);
}

bool Led::handleToggleAmbientMode(){
    AMBIENT_MODE = !AMBIENT_MODE;
}

bool Led::handleToggleState(){
    STATE_ON = !STATE_ON;
    
    applyChange();
}

bool Led::handleToggleState(bool state){
    STATE_ON = state;

    applyChange();
}

bool Led::handleColorChange(int code){
    switch (code)
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
}

const bool Led::isAmbient(){
    return AMBIENT_MODE;
}

bool Led::applyChange(){
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