/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "socket.hpp"

namespace pio
{
  static void ioCB(EV_P_  ev_io *watcher, int events)
  {
    int request_close = 0;
    ((Socket*)(watcher->data))->ioCallback(watcher, events);
  }

  Socket::Socket(EventLoop *loop):
    fd_(-1), status_(socketUnknown),
    loop_(loop)
  {
    ev_init(&read_watcher_, &ioCB);
    ev_init(&write_watcher_, &ioCB);
    ev_init(&error_watcher_, &ioCB);
    read_watcher_.data = this;
    write_watcher_.data = this;
    error_watcher_.data = this;
  }

  void Socket::ioCallback(ev_io *watcher, int events)
  {
    int request_close = 0;
    if((events & EV_READ) && read_cb_)
      read_cb_(this);

    if(events & EV_WRITE){
      if(status_ == socketConnecting)
	status_ = socketConnected;
      
      if(write_cb_)
	write_cb_(this);
    }
    
    if((events & EV_ERROR) && error_cb_){
      request_close = 1;
      error_cb_(this, -1);
    }
    
    if (request_close){
      close();
    }
  }

  int Socket::open()
  {				
    // if already opened
    assert((status_ == socketClosed) || (status_ == socketUnknown));
    int ret;
    
    ret = createSocket();
    if(ret < 0)
      goto error;
    
    if(open(ret, socketOpened) < 0)
      goto error;
    
    return 0;
  error: 
    return ret;
  }
  
  
  int Socket::open(int fd, int status)
  {
    int ret = fcntl(fd, F_SETFL, O_NONBLOCK);
    if(ret<0)
      return ret;
    
    fd_ = fd;
    status_ = status;
    return 0;
  }
  
  // close this socket
  int Socket::close()
  {
      if(fd_>0){
	loop_->unWatch(&read_watcher_);
	loop_->unWatch(&write_watcher_);
	loop_->unWatch(&error_watcher_);
	
	::close(fd_);
	status_ = socketClosed;	
	fd_ = 0;
      }
      return 0;
  }

  int Socket::startWatch(ev_io *watcher, int events)
  {
    assert((status_ != socketUnknown) && (status_ != socketClosed));

    ev_io_set(watcher, fd_, events);
    loop_->watch(watcher);

    return 0;
  }

  int Socket::stopWatch(ev_io *watcher)
  {
    loop_->unWatch(watcher);
    return 0;
  }
  
  // the socket becomes readable
  void Socket::onRead(io_cb cb)
  {
    assert(fd_>=0);
    read_cb_ = cb;
    if(read_cb_)
      startWatch(&read_watcher_, EV_READ);
    else
      stopWatch(&read_watcher_);
  }

  // the socket becomes wriable
  void Socket::onWrite(io_cb cb)
  {
    assert(fd_>=0);
    write_cb_ = cb;
    if(write_cb_)
      startWatch(&write_watcher_, EV_WRITE);
    else
      stopWatch(&write_watcher_);
  }

  // the socket has error
  void Socket::onError(error_cb cb)
  {
    assert(fd_>=0);
    error_cb_ = cb;
    if(error_cb_)
      startWatch(&error_watcher_, EV_ERROR);
    else
      stopWatch(&error_watcher_);
  }
}