#include <errno.h>

#include "test_common.hpp"

using namespace pio;

const int buf_size = 1<<10;
uint8_t buf[buf_size];
int read_pos = 0;
int write_pos = 0;


EventLoop *loop = NULL;

void write_cb(Socket *sk)
{
  int ret = 0;
  int write_size = 0;
  write_size = write_pos - read_pos;
  if(write_size){
    ret = sk->write(buf+read_pos, write_size);

    if(ret < 0){
      if( ret == EAGAIN)
	return;
      perror("write error:");
      delete sk;
      loop->stop();
    }
    printf("write  %d bytes\n", ret);
    read_pos += ret;
    if(read_pos == buf_size){
      read_pos = 0;
      write_pos = 0;
    }
  }
}

void read_cb(Socket *sk)
{
  if(write_pos == buf_size)
    return;
  
  int ret = sk->read(buf + write_pos, buf_size - write_pos);

  if(ret <0){
    if( ret == EAGAIN)
      return;
    
    perror("error in read:");
    delete sk;
    loop->stop();
  }else if(ret == 0){
    printf("a socket is closed\n");
    delete sk;
  }else{
    printf("read %d bytes\n", ret);
    write_pos += ret;
  }
}

void listen_cb(Socket *sk)
{	
  TCPServerSocket* server_sk = reinterpret_cast<TCPServerSocket*>(sk);
  TCPSocket *csk = server_sk->accept();
  csk->onRead(read_cb);
  csk->onWrite(write_cb);
}

int main(int argc, char *argv[])
{
  int ret = 0;
  TCPServerSocket *sk = NULL;
  loop = init_loop();
  if(!loop){
    exit(-1);
  }

  sk = new TCPServerSocket(loop);
  ret = sk->open();
  if(ret<0){
    perror("error when open tcp server socket\n");
    goto sk_error;
  }
    
  sk->onRead(listen_cb);    
  ret = sk->listen("0.0.0.0", 9600);
  if(ret < 0){
    printf("listen error\n");
    goto sk_error;
  }

  loop->run();
  return 0;
  
 sk_error:
  delete sk;
  delete loop;
  return -1;
}
