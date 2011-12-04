/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __EVENT_LOOP_HPP
#define __EVENT_LOOP_HPP
#include <ev.h>


namespace pio{
  class EventLoop{
  public:
    EventLoop();
    virtual ~EventLoop();
    
    int init();
    int run();
    int stop();
    
    int watch(ev_io *watcher);
    int unWatch(ev_io *watcher);
    
    int watchTimer(ev_timer *timer);
    int unWatchTimer(ev_timer *timer);
    
  private:
    struct ev_loop *loop_;
  };
  
}//namespace pio

#endif
