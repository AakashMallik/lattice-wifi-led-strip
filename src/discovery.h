#ifndef DISCOVERY
#define DISCOVERY

#include <Arduino.h>

class Discovery {
public:
  static bool isAttached;
  static String dock_link;

  static bool attach(String dock_link);
  static bool detach();
};

#endif