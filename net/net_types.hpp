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
    socketRead,
    socketWrite,
    socketError,
  };

  class Socket;
  class SocketEventListener{
  public:
    virtual void notify(Socket *socket, int events) = 0;
  };
  
}//namespace pio

#endif
