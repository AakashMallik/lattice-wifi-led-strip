// arduino libs
#include <Arduino.h>

class InbuiltLedInterface {

public:
  InbuiltLedInterface();
  bool prepare();
  bool playPattern(int &patternIndex, int &delay);
};