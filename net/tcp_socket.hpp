/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __TCP_SOCKET_HPP
#define __TCP_SOCKET_HPP
#include "socket.hpp"
#include "../event_loop.hpp"

namespace pio
{
  class TCPSocket: public Socket{
  public:
    TCPSocket(EventLoop *loop);
    
    virtual ~TCPSocket(){close();}
    
    int read(void *buf, int size);
    int write(void *buf, int size);
    int createSocket();
  };
}//namespace pio
  

#endif
