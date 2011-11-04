/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#include <string.h>

#include "tcp_server_socket.hpp"

namespace pio{
  int TCPServerSocket::Open(const char *ip, uint16_t port){
    int ret;
    int yes = 1;
    listen_ip_ = strdup(ip);
    listen_port_ = port;
    struct sockaddr_in addr = ip4_addr(ip, port);
    
    ret = CreateSocket();
    if (ret < 0)
      goto error;
      
    ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if(ret < 0)
      goto sock_error;
      
    ret = bind(fd_, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if(ret < 0)
      goto sock_error;
      
    ret = listen(fd_, backlog_);
    if(ret<0)
      goto sock_error;
      
  sock_error:
    close(fd_);
    status_ = socketClosed;
  error:
    return ret;
  }
  
}//namespace pio
