#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>

#include "test_common.hpp"
EventLoop *loop = NULL;

char buf[] = "hello";

class PingClient: public SocketEventListener
{
public:
  PingClient(TCPClientSocket *sk, const char *ip, uint16_t port):
    client_sk_(sk), connected_(false)
  {
    int ret;
    sk->onWrite(this);

    ret = sk->connect(ip, port);
    if(ret < 0){
      perror("Cannot connect to server:");
      exit(-1);
    }
  }
  
  void read(Socket *sk)
  {
    char buf1[1024];
    int ret=0;
    static int cur_pos = 0;
  
    ret = sk->read(buf1+cur_pos, 1024-cur_pos);
    if(ret <0){
      if( ret == EAGAIN)
	return;
      perror("error in read:");
      delete sk;
      loop->stop();
    }else if(ret>0){

      cur_pos += ret;
      printf("read %d bytes %d\n", ret, cur_pos);
    }
    if((ret==0) || (cur_pos == sizeof(buf))){
      printf(">>> %s\nBye\n",buf);
      delete sk;
      loop->stop();
    }
  }

  void write(Socket *sk)
  {
    int ret = 0;
    ret = sk->write(buf, sizeof(buf));
    if(ret < 0){
      if( ret == EAGAIN)
	return;
      perror("write error:");
      delete sk;
      loop->stop();
    }else
      sk->onWrite(NULL);
  }

  void notify(Socket *sk, int event)
  {
    if(!connected_ && event == socketWrite){
      sk->onRead(this);
      connected_ = true;
      return;
    }
    if(event == socketRead){
      read(sk);
    }else if(event == socketWrite){
      write(sk);
    }else{
      printf("Internal error\n");
      exit(-1);
    }
  }
private:
  TCPClientSocket *client_sk_;
  bool connected_;
};

int main(int argc, char *argv[])
{
  int ret;
  TCPClientSocket *sk=NULL;
  PingClient *client =NULL;

  if( argc!= 3){
    fprintf(stderr, "Usage: %s ip port\n", argv[0]);
    return -1;
  }
  const char *ip = argv[1];
  uint16_t port = (uint16_t)atoi(argv[2]);

  loop = init_loop();
  if(!loop){
    goto error;
  }
  sk = create_client_socket(loop);
  if(!sk)
    goto sk_error;

  client = new PingClient(sk, ip, port);
  
  loop->run();

  delete client;
  return 0;
  
 sk_error:
  delete loop;
 error:
  return -1;
}
