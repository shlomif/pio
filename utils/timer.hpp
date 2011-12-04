/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __PIO_TIMER_HPP
#define __PIO_TIMER_HPP
#include "event_loop.hpp"

namespace pio
{
  class Timer;
  class TimerCallback
  {
  public:
    virtual void run(Timer *timer) = 0;
  };
  
  class Timer
  {
  public:
    Timer(EventLoop *loop, TimerCallback *cb);

    virtual ~Timer(){
      stop();
    }

    // start the periodical timer after "delay" seconds 
    void start(double delay, double interval);
    // start the onetime timter after "delay" seconds
    void startOnce(double delay);
    //stop the timer
    void stop();
    // notify the event
    void notify();
  private:
    TimerCallback *cb_;
    EventLoop *loop_;
    ev_timer timer_;
    int started_;
  };
}
#endif
