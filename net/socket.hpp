/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __SOCKET_HPP
#define __SOCKET_HPP
#include <unistd.h>

#include "net_util.hpp"
#include "net_types.hpp"

namespace pio{
  class Socket {
  public:
    virtual ~Socket(){
      if(fd_>0){
	close(fd_);
	fd_ = 0;
      }
      status_ = socketClosed;
    }
    
    int fd(){ return fd_; }
    int status(){ return status_; }
  protected:
    Socket():fd_(-1), status_(socketClosed){}
    int fd_;
    int status_;
  };
}

#endif
