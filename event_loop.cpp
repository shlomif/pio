/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#include <assert.h>
#include <ev.h>

#include "event_loop.hpp"


namespace pio{
  EventLoop::EventLoop():
    loop_(NULL)
  {
  }

  EventLoop::~EventLoop()
  {
    stop();
  }
  
  int EventLoop::init()
  {
    if(loop_)
      return 0;
    loop_ = ::ev_default_loop(EVFLAG_AUTO | EVFLAG_NOENV);
    if(!loop_)
      return -1;
  }
  
  int EventLoop::run()
  {
    assert(loop_);
    ev_loop(loop_, 0);
    return 0;
  }
  
  int EventLoop::stop()
  {
    if(loop_)
      ::ev_unloop(loop_, EVUNLOOP_ONE);
    return 0;
  }
  
  int EventLoop::watch(ev_io *watcher)
  {
    ::ev_io_start(loop_, watcher);
    return 0;
  }
  
  int EventLoop::unWatch(ev_io *watcher)
  {
    ::ev_io_stop(loop_, watcher);
    return 0;
  }
  
}
