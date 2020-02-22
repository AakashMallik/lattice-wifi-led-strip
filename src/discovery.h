#ifndef DISCOVERY
#define DISCOVERY

#include <Arduino.h>

class Discovery {
public:
  static bool isAttached;
  static String hub_address;

  static bool attach(String ip, String port);
  static bool detach();
};

#endif