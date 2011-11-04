/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __TCP_SERVER_SOCKET_HPP
#define __TCP_SERVER_SOCKET_HPP
#include <stdint.h>

#include "tcp_socket.hpp"

namespace pio{
  class TCPServerSocket: public TCPSocket{
  public:
    TCPServerSocket(int backlog=128):
      TCPSocket(),
      backlog_(backlog){
    }
    int Open(const char *ip, uint16_t port);
  private:
    char *listen_ip_;
    uint16_t listen_port_;
    int backlog_;
  };
  
}//namespace pio

#endif
