
#include "event_loop.hpp"
#include "net/net.hpp"

using namespace pio;

EventLoop* init_loop()
{
  int ret;
  EventLoop *loop = new EventLoop();
  ret = loop->init();
  if(ret<0){
    printf("error in inialize the loop\n");
    delete loop;
    return NULL;
  }
  return loop;
}


TCPClientSocket *create_client_socket(EventLoop *loop)
{
  TCPClientSocket *sk = NULL;
  int ret;
  sk = new TCPClientSocket(loop);
  ret = sk->open();
  if(ret<0){
    printf("error when open tcp client socket\n");
    delete sk;
    return NULL;
  }
  return sk;
}


int connect_server(TCPClientSocket *sk, const char *ip, uint16_t port, io_cb cb)
{
  int ret;
  sk->onWrite(cb);
  ret = sk->connect(ip, port);
  return ret;
}
