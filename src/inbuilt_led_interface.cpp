#include <inbuilt_led_interface.h>

InbuiltLedInterface::InbuiltLedInterface() {}

bool InbuiltLedInterface::prepare() {
  pinMode(LED_BUILTIN, OUTPUT);
  return true;
}

bool InbuiltLedInterface::playPattern(int &patternIndex, int &delay) {
  switch (patternIndex) {
  case 1:
    Serial.println("lights camera actions");
    break;

  default:
    break;
  }
  return true;
}