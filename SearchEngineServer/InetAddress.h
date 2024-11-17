/**
 * @brief 网络地址类
 */
#ifndef _INETADDRESS_H
#define _INETADDRESS_H

#include <arpa/inet.h>
#include <netinet/in.h>

#include <string>

using std::string;

class InetAddress {
 public:
  /**
   * @brief 构造函数
   * @param ip ip地址
   * @param port 端口号
   */
  InetAddress(const string& ip, unsigned short port) {
    _addr.sin_family = AF_INET;                     // ipv4
    _addr.sin_port = htons(port);                   // 端口号
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());  // ip地址
  }
  /**
   * @brief 获取地址结构体指针
   * @return struct sockaddr_in* 地址结构体指针
   */
  struct sockaddr_in* getInetAddressPtr() {
    return &_addr;
  }

 private:
  struct sockaddr_in _addr;  // 地址结构体
};

#endif  //_INETADDRESS_H