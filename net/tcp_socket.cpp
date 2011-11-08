#include <assert.h>
#include <errno.h>

#include "tcp_socket.hpp"
#include "net_types.hpp"

namespace pio
{
  TCPSocket::TCPSocket(EventLoop *loop):
    Socket(loop)
  {
  }
  
  int TCPSocket::createSocket()
  {
    return socket(AF_INET, SOCK_STREAM, 0);
  }
  
  int TCPSocket::read(void *buf, int size)
  {
    int ret;
    assert(status_ == socketConnected);
    ret = ::read(fd_, buf, size);
    assert(errno != ENOTCONN);
    assert(errno != EWOULDBLOCK);
    return ret;
  }
  
  int TCPSocket::write(void *buf, int size)
  {
    int ret;
    assert(status_ == socketConnected);
    ret = ::write(fd_, buf, size);
    assert(errno != ENOTCONN);
    assert(errno != EWOULDBLOCK);

    return ret;
  }
  
}
