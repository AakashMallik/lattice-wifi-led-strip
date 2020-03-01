#include <Arduino.h>
#include <discovery.h>

bool Discovery::isAttached = false;
String Discovery::dock_link = "";

bool Discovery::attach(String dock_link){
    isAttached = true;
    dock_link = dock_link;
    return true;
}  

bool Discovery::detach(){
    isAttached = false;
    return true;
}