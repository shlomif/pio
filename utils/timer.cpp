/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */

#include <assert.h>

#include "timer.hpp"
#include "event_loop.hpp"

namespace pio
{
  static void timerCB(EV_P_ ev_timer *w, int events)
  {
    ((Timer*)(w->data))->notify();
  }
  
  Timer::Timer(EventLoop *loop, TimerCallback *cb):
    loop_(loop), cb_(cb), started_(0)
  {
  }
  
  void Timer::start(double delay, double interval)
  {
    assert(interval > 0.);
    assert(started_ == 0);
    ev_timer_init(&timer_, timerCB, delay, interval);
    timer_.data = this;
    loop_->watchTimer(&timer_);
    started_ = 1;
  }
  
  void Timer::startOnce(double delay)
  {
    assert(started_ == 0);
    ev_timer_init(&timer_, timerCB, delay, 0.);
    timer_.data = this;
    loop_->watchTimer(&timer_);
    started_ = 1;
  }
  
  void Timer::stop()
  {
    if(!started_)
      return;
    loop_->unWatchTimer(&timer_);
    started_ = 0;
  }

  void Timer::notify()
  {
    cb_->run(this);
  }
}
