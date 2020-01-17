#ifndef UDP_SERVER
#define UDP_SERVER

#include <ESPAsyncUDP.h>

class UdpInterface {
  static AsyncUDP *udp;

public:
  static bool prepare(int a, int b, int c, int d, int multicast_port);
  static bool broadcast();
};

#endif