/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __TCP_CLIENT_SOCKET_HPP
#define __TCP_CLIENT_SOCKET_HPP

#include "tcp_socket.hpp"
#include "../event_loop.hpp"

namespace pio
{
  class TCPClientSocket: public TCPSocket
  {
  public:
    TCPClientSocket(EventLoop *loop):
      TCPSocket(loop)
    {
    }
    
    // Asynronoous connect to remote ip:port.
    // When connection is made, socket become writable; User should monitor
    // write event to know if connection is made
    int connect(const char *ip, uint16_t port);
  };
}

#endif
