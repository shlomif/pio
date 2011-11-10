#include <errno.h>

#include "test_common.hpp"

using namespace pio;


EventLoop *loop = NULL;


class EchoServer:public SocketEventListener
{
public:
  EchoServer(TCPServerSocket *sk):
    server_sk_(sk), buf_size_(1<<10), buf_(new char[buf_size_]),
    read_pos_(0), write_pos_(0)
  {
    int ret;
    sk->onRead(this);
    ret = sk->listen("0.0.0.0", 9600);
    if(ret < 0){
      printf("listen error\n");
      exit(-1);
    }
  }
  
  void write(Socket *sk)
  {
    int ret = 0;
    int write_size = 0;
    write_size = write_pos_ - read_pos_;
    if(write_size){
      ret = sk->write(buf_+read_pos_, write_size);

      if(ret < 0){
	if( ret == EAGAIN)
	  return;
	perror("Error happens in writing a socket");
	delete sk;
      }
      printf("write  %d bytes\n", ret);
      read_pos_ += ret;
      if(read_pos_ == buf_size_){
	read_pos_ = 0;
	write_pos_ = 0;
      }
    }
  }

  void read(Socket *sk)
  {
    if(write_pos_ == buf_size_)
      return;
  
    int ret = sk->read(buf_ + write_pos_, buf_size_ - write_pos_);

    if(ret <0){
      if( ret == EAGAIN)
	return;
      perror("Error happens in reading a socket:");
      delete sk;
    }else if(ret == 0){
      printf("a socket is closed\n");
      delete sk;
    }else{
      printf("read %d bytes\n", ret);
      write_pos_ += ret;
    }
  }
  
  void notify(Socket *sk, int event)
  {
    if( (sk== server_sk_) && (event == socketRead)){
      // accept
      TCPSocket *csk = server_sk_->accept();
      csk->onRead(this);
      csk->onWrite(this);
      return;
    }
    if(event == socketRead){
      this->read(sk);
    }else if(event == socketWrite){
      this->write(sk);
    }else{
      printf("Internal error occurred in the server\n");
      exit(-1);
    }
  }

private:
  TCPServerSocket *server_sk_;
  int buf_size_;
  char *buf_;
  int read_pos_;
  int write_pos_;
};


int main(int argc, char *argv[])
{
  int ret = 0;
  TCPServerSocket *sk = NULL;
  EchoServer *server;
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
    
  server = new EchoServer(sk);
  loop->run();
  return 0;
  
 sk_error:
  delete sk;
  delete loop;
  return -1;
}
