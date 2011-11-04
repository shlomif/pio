/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __EVENT_LOOP_HPP
#define __EVENT_LOOP_HPP


namespace pio{
  class EventLoop{
  public:
    EventLoop();
    virtual ~EventLoop();
    int watch(Socket *socket, int io);
    int unwatch(Socket *socket, int io);
    int run();
    int stop();
  };
  
}//namespace pio

#endif
