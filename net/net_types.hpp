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
  
  
}//namespace pio

#endif
