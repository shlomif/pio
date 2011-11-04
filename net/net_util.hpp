/* Author: Wenhao Xu <xuwenhao2008@gmail.com> */
#ifndef __NET_UTIL_HPP
#define __NET_UTIL_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>

namespace pio{
  
  struct sockaddr_in ip4_addr(const char* ip, uint16_t port){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    return addr;
  }
  
}//namespace pio

#endif
