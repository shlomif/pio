/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#include <string.h>
#include <assert.h>

#include "tcp_server_socket.hpp"

namespace pio
{
  int TCPServerSocket::listen(const char *ip, uint16_t port)
  {
    int ret;
    int yes = 1;
    
    assert(status_ == socketOpened);
    assert(fd_>=0);
    
    listen_ip_ = strdup(ip);
    listen_port_ = port;
    struct sockaddr_in addr = ip4_addr(ip, port);
      
    ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if(ret < 0)
      goto sock_error;
      
    ret = bind(fd_, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if(ret < 0)
      goto sock_error;
      
    ret = ::listen(fd_, backlog_);
    if(ret<0)
      goto sock_error;
    
    status_ = socketListenning;
    
    return 0;
  sock_error:
    close();
  error:
    return ret;
  }
  
  TCPSocket *TCPServerSocket::accept()
  {  
    struct sockaddr addr;
    socklen_t addrlen;
    int ret;
    TCPSocket *sk=NULL;
    assert(status_ == socketListenning);
    
    ret = ::accept(fd_, &addr, &addrlen);
    if(ret < 0){
      goto error;
    }
    
    // create a new tcp socket 
    sk = new TCPSocket(loop_);
    if(sk->open(ret, socketConnected) < 0)
      goto sk_error;
    
    return sk;
  sk_error:
    delete sk;
  error:
    return NULL;
  }
  
}//namespace pio
