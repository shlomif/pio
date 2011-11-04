/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __NET_TYPES_HPP
#define __NET_TYPES_HPP

namespace pio{
  enum SocketStatus{
    socketClosed = 0x0,
    socketListen,
    socketConnecting,
    socketConnected,
  };
}//namespace pio

#endif
