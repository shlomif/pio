/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __SOCKET_HPP
#define __SOCKET_HPP
#include <unistd.h>
#include <ev++.h>

#include "../event_loop.hpp"
#include "net_util.hpp"
#include "net_types.hpp"

namespace pio
{
  class Socket 
  {
  public:
    Socket(EventLoop *loop);

    virtual ~Socket(){
      close();
    }
    
    int fd(){ return fd_; }
    int status(){ return status_; }
    
    // open this Socket: create socket fd and other initialization
    int open();
    
    // fd is the socket already created, just do other initialization
    int open(int fd, int status);
    // close this socket
    // when the socket is closed, all event watchers are gone.
    int close();
    // the socket becomes readable
    void onRead(SocketEventListener *listener);
    
    // the socket becomes wriable
    void onWrite(SocketEventListener *listener);

    // unexpected error happens usually due to the program bugs.
    // a good program should never get this error callback
    // After error happens, the socket will be closed and
    // therefore close_cb will get called afterwards
    void onError(SocketEventListener *listener);

    //int setKeepAlive(int enable=0);

    // do a best effort read up to size bytes;
    // If there is not enough bytes readable, less than size bytes returned.
    // Upon reading EOF, 0 will be returned.
    // When error happens, -1 will be returned and errno indecates the error.
    // If the connection is reset by remote during read, the socket will be closed.
    virtual int read(void *buf, int size) = 0;
    
    // do a best effort write up to size bytes;
    // The number of bytes successfully written will be returned;
    // When error happens, -1 will be returned;
    // If the connection is reset by remote during read, the socket will be closed.
    virtual int write(void *buf, int size) = 0;
    
    void ioCallback(ev_io *watcher, int events);
  protected:
    virtual int createSocket() = 0;
    
    int fd_;
    int status_;
    ev_io read_watcher_;
    ev_io write_watcher_;
    ev_io error_watcher_;

    SocketEventListener *read_listener_;
    SocketEventListener *write_listener_;
    SocketEventListener *error_listener_;
    
    EventLoop *loop_;
    int startWatch(ev_io *watcher, int events);
    int stopWatch(ev_io *watcher);
    
  };
}

#endif
