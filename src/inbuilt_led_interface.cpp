#include <inbuilt_led_interface.h>

bool InbuiltLedInterface::prepare() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  return true;
}

bool InbuiltLedInterface::playPattern(int delay_time, int patternIndex) {
  switch (patternIndex) {
  case 1:
    // Improve
    for (int i = 2; i < 20; i++) {
      digitalWrite(LED_BUILTIN, (i % 2 == 0) ? HIGH : LOW);
      delay(delay_time/i);
    }
    break;

  default:
    break;
  }
  return true;
}