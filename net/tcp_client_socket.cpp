/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include "tcp_client_socket.hpp"

namespace pio
{
  int TCPClientSocket::connect(const char *ip, uint16_t port)
  {
    int ret = 0;
    assert(status_ == socketOpened);
    
    struct sockaddr_in addr = ip4_addr(ip, port);
    ret = ::connect(fd_, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if((ret < 0) && (errno != EINPROGRESS))
      return ret;

    status_ = socketConnecting;
    return 0;
  }
}
