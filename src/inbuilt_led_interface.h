#ifndef INBUILT_LED_INTERFACE
#define INBUILT_LED_INTERFACE

// arduino libs
#include <Arduino.h>

class InbuiltLedInterface {
  static bool isOn;

public:
  static bool prepare();
  static bool playPattern(int delay_time, int patternIndex);
};

#endif