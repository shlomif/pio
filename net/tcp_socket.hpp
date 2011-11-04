/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __TCP_SOCKET_HPP
#define __TCP_SOCKET_HPP
#include "socket.hpp"

namespace pio{
  class TCPSocket: public Socket{
  public:
    virtual ~TCPSocket(){}
  protected:
    int CreateSocket();
  };
}//namespace pio
  

#endif
