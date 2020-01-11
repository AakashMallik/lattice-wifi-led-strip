#ifndef UDP_SERVER
#define UDP_SERVER

#include <ESPAsyncUDP.h>

class UdpInterface {
  AsyncUDP udp;

public:
  UdpInterface(int a, int b, int c, int d, int multicast_port);
  bool prepare();
  bool broadcast();
};

#endif