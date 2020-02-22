#include <Arduino.h>
#include <discovery.h>

bool Discovery::isAttached = false;
String Discovery::hub_address = "";

bool Discovery::attach(String ip, String port){
    isAttached = true;
    hub_address = "http://" + ip + ":" + port + "/";
    return true;
}  

bool Discovery::detach(){
    isAttached = false;
    return true;
}