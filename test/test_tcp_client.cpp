#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>

#include "test_common.hpp"
EventLoop *loop = NULL;

void read_cb(Socket *sk)
{
  char buf[1024];
  int ret=0;
  static int cur_pos = 0;
  
  ret = sk->read(buf+cur_pos, 1024-cur_pos);
  if(ret <0){
    if( ret == EAGAIN)
      return;
    perror("error in read:");
    delete sk;
    loop->stop();
  }else if(ret == 0){
    printf(">>> %s\nBye\n",buf);
    delete sk;
    loop->stop();
  }else{
    printf("read %d bytes\n", ret);
    cur_pos += ret;
  }
}

void write_cb(Socket *sk)
{
  //write "hello"
  char buf[] = "hello";
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

void connect_cb(Socket *sk)
{
  TCPClientSocket* client_sk = reinterpret_cast<TCPClientSocket*>(sk);
  client_sk->onRead(read_cb);
  client_sk->onWrite(write_cb);
}


int main(int argc, char *argv[])
{
  int ret;
  TCPClientSocket *sk=NULL;
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

  ret = connect_server(sk, ip, port, connect_cb);
  if(ret < 0){
    perror("Cannot connect to server:");
    goto connect_error;
  }
  
  loop->run();
  
  return 0;
  
 connect_error:
  delete sk;
 sk_error:
  delete loop;
 error:
  return -1;
}
