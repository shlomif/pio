/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __TCP_SERVER_SOCKET_HPP
#define __TCP_SERVER_SOCKET_HPP
#include <stdint.h>

#include "tcp_socket.hpp"
#include "../event_loop.hpp"

namespace pio{
  class TCPServerSocket: public TCPSocket
  {
  public:
    TCPServerSocket(EventLoop *loop, int backlog=128):
      TCPSocket(loop),
      backlog_(backlog)
    {
    }
    // listen on the ip:port
    // return 0 if succeed, <0 if failed
    // when there is an incoming connection request, a read event will be issued
    int listen(const char *ip, uint16_t port);

    TCPSocket *accept();
  private:
    char *listen_ip_;
    uint16_t listen_port_;
    int backlog_;
  };

}//namespace pio

#endif
