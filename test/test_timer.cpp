#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/timer.hpp"
#include "event_loop.hpp"

using namespace pio;

class Clock: public TimerCallback
{
public:
  void run(Timer *timer)
  {
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "%s", asctime (timeinfo) );
  }
};

int main(int argc, char *argv[])
{
  int ret = 0;
  EventLoop* loop = new EventLoop();
  ret = loop->init();
  if(ret <0){
    printf("Error when creating event loop\n");
    exit(-1);
  }
  TimerCallback *cb = new Clock();
  Timer *t = new Timer(loop, cb);
  t->start(1, 1);

  Timer *t2 = new Timer(loop, cb);
  t2->startOnce(0.2);

  loop->run();
  return 0;
}
