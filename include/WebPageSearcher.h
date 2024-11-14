/**
 * Project SearchEngine
 */

#ifndef _WEBPAGESEARCHER_H
#define _WEBPAGESEARCHER_H

class WebPageSearcher {
 public:
  string doQuery();

 private:
  string _sought;
  TcpConnectionPtr _conn;
};

#endif  //_WEBPAGESEARCHER_H