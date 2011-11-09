/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __NET_TYPES_HPP
#define __NET_TYPES_HPP

namespace pio{
  enum SocketStatus{
    socketUnknown = 0x0,
    socketOpened,
    socketClosed,
    socketListenning,
    socketConnecting,
    socketConnected,
  };
  enum SocketEvent{
    READ,
    WRITE,
    ERROR,
  };
  
  class SocketEventListener{
    virtual onRead() = 0;
    virtual onWrite() = 0;
    virtual onError() = 0;
  };
  
}//namespace pio

#endif
